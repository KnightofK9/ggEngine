using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;
using System.Windows.Interop;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;
using ggMapEditor.Commands;
using ggMapEditor.Views;
using ggMapEditor.Views.Controls;
using ggMapEditor.Helpers;

namespace ggMapEditor.ViewModels
{
    public class MapAreaTabViewModel : Main.DockTabViewModel
    {
        public UIElement container;

        #region Private members
        private int columnCount;
        private int rowCount;
        private int tileWidth;
        private int tileHeight;

        //private ObservableCollection<DragableLayout> listChild;
        private Dictionary<Point, DragableLayout> hashMap; //Matrix Map (simulate container)
        //private ObservableCollection<Models.Tile> listTile;
        #endregion

        #region Constructors
        public MapAreaTabViewModel(Models.TileMap map)
        {
            //ListTile = new ObservableCollection<Models.Tile>();
            HashMap = new Dictionary<Point, DragableLayout>();

            InitGrid(map);
        }
        private void InitGrid(Models.TileMap map)
        {
            if (map.leafWidth == 0 || map.leafHeight == 0
                || map.row == 0 || map.column == 0)
                return;

            //necessary variables
            columnCount = map.column;
            rowCount = map.row;
            tileWidth = map.leafWidth;
            tileHeight = map.leafHeight;

            // Add Cells
            for (int i = 0; i < rowCount; i++)
                for (int k = 0; k < columnCount; k++)
                {
                    DragableLayout layout = new DragableLayout();
                    //layout.id = QuadTree.QuadTree.GetPositionQuadTree(new System.Drawing.Point((int)(i*TileSize), (int)(k*TileSize)), grid as Panel);
                    Canvas.SetTop(layout, i * 32);
                    Canvas.SetLeft(layout, k * 32);
                    layout.Width = tileWidth;
                    layout.Height = tileHeight;
                    //layout.ChildChanged += DragableLayout_ChildChange;

                    HashMap.Add(new Point(k, i), layout);
                }
        }

        #endregion

        #region Properties
        public Rect TileViewPort
        {
            get { return new Rect(0, 0, tileWidth, tileHeight); }
        }
        public int MapWidth
        {
            get { return tileWidth * columnCount; }
        }
        public int MapHeight
        {
            get { return tileHeight * rowCount; }
        }

        public ObservableCollection<DragableLayout> ListChild
        {
            get { return new ObservableCollection<DragableLayout>(HashMap.Values); }
        }
        public Dictionary<Point, DragableLayout> HashMap
        {
            get { return hashMap; }
            set
            {
                hashMap = value;
                RaisePropertyChanged(nameof(ListChild));
            }
        }
        public ObservableCollection<Models.Tile> HashMapChild
        {
            get
            {
                var listChild = new ObservableCollection<Models.Tile>();

                foreach (var c in hashMap)
                {
                    var dragLayout = c.Value;
                    if (dragLayout.GetChildCount() == 0 || dragLayout.GetChildAt(0) == null)
                        continue;
                    Views.Controls.Tile cTile = dragLayout.GetChildAt(0) as Views.Controls.Tile;

                    var mTile = new Models.Tile();
                    mTile.tileId = cTile.ImgId;
                    mTile.tilesetKey = cTile.TilesetKey;
                    mTile.isCollidedObject = c.Value.GetChildCount() == 0 ? true : false;

                    Point position = c.Key;
                    position.X *= tileWidth + 1;    // Cộng 1 để lúc xuất không bị nhầm lẫn giữa 2 node
                    position.Y *= tileHeight + 1;
                    mTile.rectPos = new Int32Rect((int)position.X, (int)position.Y, (int)cTile.TileWidth, (int)cTile.TileHeight);

                    listChild.Add(mTile);
                }
                return listChild;
            }
        }
        #endregion

        #region Mouse Events
        #region Commands
        public RelayCommand mouseMoveCommand;
        public RelayCommand MouseMoveCommand
        {
            get
            {
                if (mouseMoveCommand == null)
                    return mouseMoveCommand = new RelayCommand(param => ExecuteMouseMove((MouseEventArgs)param));
                return mouseMoveCommand;
            }
            set { mouseMoveCommand = value; }
        }

        public RelayCommand mouseLeftButtonDownCommand;
        public RelayCommand MouseLeftButtonDownCommand
        {
            get
            {
                if (mouseLeftButtonDownCommand == null)
                    return mouseLeftButtonDownCommand = new RelayCommand(param => ExecuteMouseLeftButtonDown((MouseEventArgs)param));
                return mouseLeftButtonDownCommand;
            }
            set { mouseLeftButtonDownCommand = value; }
        }
        #endregion

        #region Funcs
        private void ExecuteMouseMove(MouseEventArgs e)
        {
            if (Mouse.LeftButton == MouseButtonState.Pressed)
            {
                if (Helpers.ToolsEventHandle.DrawTool == ToolTypes.Block)
                    DrawBlock();

                if (Helpers.ToolsEventHandle.DrawTool == ToolTypes.Pen)
                    DrawTile(Helpers.StaticHelper.currentCTile);

                if (Helpers.ToolsEventHandle.DrawTool == ToolTypes.Eraser)
                    Eraser();
            }
        }

        private void ExecuteMouseLeftButtonDown(MouseEventArgs e)
        {
            if (Helpers.ToolsEventHandle.DrawTool == ToolTypes.Block)
                DrawBlock();

            if (Helpers.ToolsEventHandle.DrawTool == ToolTypes.Pen)
            {
                //DrawMultiTile(CacheElementCollection.Elements);
                DrawTile(Helpers.StaticHelper.currentCTile);
            }


            if (Helpers.ToolsEventHandle.DrawTool == ToolTypes.Eraser)
                Eraser();
        }
        #endregion
        #endregion


        #region Others
        //public void DragableLayout_ChildChange(object sender, DragableLayoutChildEventArgs e)
        //{
        //    if (ListTile != null)
        //    {
        //        if (e.isChildRemoved)
        //            ListTile.Remove(e.child);
        //        else
        //            ListTile.Add(e.child);
        //    }
        //}
        public RenderTargetBitmap CaptureImage()
        {
            if (container == null)
                return null;

            Size size = new Size(columnCount * tileWidth, rowCount * tileHeight);
            container.Measure(size);

            var rtb = new RenderTargetBitmap(
                columnCount * tileWidth,
                rowCount * tileHeight,
                96, //dpi x 
                96, //dpi y 
                PixelFormats.Pbgra32);
            rtb.Render(container);
            return rtb;
        }


        private void DrawMultiTile(Dictionary<Point, UIElement> elements)
        {
            if (elements != null && elements.Count > 1)
            {
                var childs = elements.TranslatePositionCollection(Mouse.GetPosition(null), Mouse.GetPosition(container));
                foreach (var c in childs)
                {
                    int XcurCell = (int)c.Key.X / tileWidth;
                    int YcurCell = (int)c.Key.Y / tileHeight;

                    if (XcurCell > columnCount - 1
                        || XcurCell < 0
                        || YcurCell > rowCount - 1
                        || YcurCell < 0)
                        continue;

                    var cell = HashMap[new Point(XcurCell, YcurCell)];
                    if (cell.GetChildCount() == 0)
                        cell.AddChild(new Views.Controls.Tile(c.Value as Tile));
                }
            }
        }

        private void DrawTile(UIElement element)
        {
            if (element != null)
            {
                var cell = GetChild();
                if (cell == null) return;

                if (cell.GetChildCount() == 0 && element != null)
                    cell.AddChild(new Views.Controls.Tile(element as Tile));
            }
        }

        private void Eraser()
        {
            var cell = GetChild();
            if (cell == null) return;

            if (cell.GetChildCount() > 0)
                cell.RemoveChild();
        }

        private void DrawBlock()
        {
            var cell = GetChild();
            if (cell == null) return;

            if (cell.GetChildCount() == 1)
            {
                int strokeThickness = 2;
                Rectangle block = new Rectangle()
                {
                    Width = tileWidth,
                    Height = tileHeight,
                    Stroke = Brushes.Green,
                    StrokeThickness = strokeThickness,
                };

                cell.AddChild(block);
            }
        }

        private DragableLayout GetChild()
        {
            Point mousePos = Mouse.GetPosition(container);
            int XcurCell = (int)mousePos.X / tileWidth;
            int YcurCell = (int)mousePos.Y / tileHeight;

            if (XcurCell > columnCount - 1
                || XcurCell < 0
                || YcurCell > rowCount - 1
                || YcurCell < 0)
                return null;

            return HashMap[new Point(XcurCell, YcurCell)];
        }
        #endregion
    }
}
