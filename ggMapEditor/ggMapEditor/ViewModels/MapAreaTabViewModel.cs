using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Drawing.Imaging;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;
using System.Windows.Interop;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using ggMapEditor.Commands;
using ggMapEditor.Views;
using ggMapEditor.Views.Controls;

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

        private ObservableCollection<DragableLayout> listChild;
        private Dictionary<string, DragableLayout> hashMap; //Matrix Map (simulate container)
        //private ObservableCollection<Models.Tile> listTile;
        #endregion

        #region Constructors
        public MapAreaTabViewModel(Models.TileMap map)
        {
            ListChild = new ObservableCollection<DragableLayout>();
            ListTile = new ObservableCollection<Models.Tile>();
            HashMap = new Dictionary<string, DragableLayout>();

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
                    layout.ChildChanged += DragableLayout_ChildChange;

                    //ListChild.Add(layout);
                    HashMap.Add(k.ToString() + i.ToString(), layout);
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
            get { return tileWidth*columnCount; }
        }
        public int MapHeight
        {
            get { return tileHeight*rowCount; }
        }

        public ObservableCollection<DragableLayout> ListChild
        {
            get { //return listChild;
                return new ObservableCollection<DragableLayout>(HashMap.Values);
            }
            set
            {
                //listChild = value;
                //RaisePropertyChanged(nameof(ListChild));
            }
        }

        public Dictionary<string, DragableLayout> HashMap
        {
            get { return hashMap; }
            set
            {
                hashMap = value;
                RaisePropertyChanged(nameof(ListChild));
            }
        }

        public ObservableCollection<Models.Tile> ListTile{ get; private set; }
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
                Point mousePos = e.GetPosition(container);
                int XcurCell = (int)mousePos.X / tileWidth;
                int YcurCell = (int)mousePos.Y / tileHeight;

                if (Helpers.StaticHelper.currentCTile != null)
                {
                    var cell = HashMap[XcurCell.ToString() + YcurCell.ToString()];
                    cell.AddChild(new Views.Controls.Tile(Helpers.StaticHelper.currentCTile));
                }
            }
        }

        private void ExecuteMouseLeftButtonDown(MouseEventArgs e)
        {
            //MessageBox.Show(e.GetPosition(container).ToString());
        }
        #endregion
        #endregion


        #region Others
        public void DragableLayout_ChildChange(object sender, DragableLayoutChildEventArgs e)
        {
            if (ListTile != null)
            {
                if (e.isChildRemoved)
                    ListTile.Remove(e.child);
                else
                    ListTile.Add(e.child);
            }
        }
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


        private void DrawTile(UIElement element)
        {

        }

        private void Eraser()
        {

        }

        private void DrawBlock()
        {

        }
        #endregion
    }
}
