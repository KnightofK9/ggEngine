using System.Collections.ObjectModel;
using System.Windows;
using System.Windows.Controls;
using ggMapEditor.Views.Controls;

namespace ggMapEditor.ViewModels
{
    class MapAreaTabViewModel : Main.DockTabViewModel
    {
        #region Private members
        private int columnCount;
        private int rowCount;
        private int tileWidth;
        private int tileHeight;

        private ObservableCollection<DragableLayout> listChild;
        #endregion

        #region Constructors
        public MapAreaTabViewModel(Models.TileMap map)
        {
            listChild = new ObservableCollection<DragableLayout>();
            InitGrid(map);
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
            get { return listChild; }
            set
            {
                listChild = value;
                RaisePropertyChanged("ListChild");
            }
        }
        #endregion

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
                    Canvas.SetTop(layout, i*32);
                    Canvas.SetLeft(layout, k*32);
                    layout.Width = tileWidth;
                    layout.Height = tileHeight;
                    
                    ListChild.Add(layout);
                }
        }


        //public ObservableCollection<object> RetrieveChilds()
        //{
            //var listChild = new ObservableCollection<object>();
            //    //Grid grid = IGrid.GetGrid() as Grid;
            //    foreach (var cell in grid.Children)
            //    {
            //        var childrens = (cell as DragableLayout).GetChildren();
            //        if (childrens.Count > 0)
            //        {
            //            Views.Controls.Tile ctrTile = childrens.First() as Views.Controls.Tile;
            //            Models.Tile tile = new Models.Tile();
            //            tile.tileId = ctrTile.ImgId;
            //            Point cellPosition = ctrTile.TransformToAncestor(grid).Transform(new Point(0, 0));
            //            tile.rectPos = new Int32Rect((int)cellPosition.X, (int)cellPosition.Y, tileWidth, tileHeight);
            //            listTile.Add(tile);
            //        }
            //    }
            //    return listTile;
        //}
        //public ObservableCollection<Models.Tile> RetrieveTiles()
        //{
        //    ObservableCollection<Models.Tile> listTile = new ObservableCollection<Models.Tile>();
        //    //Grid grid = IGrid.GetGrid() as Grid;
        //    foreach (var cell in grid.Children)
        //    {
        //        var childrens = (cell as DragableLayout).GetChildren();
        //        if (childrens.Count > 0)
        //        {
        //            Views.Controls.Tile ctrTile = childrens.First() as Views.Controls.Tile;
        //            Models.Tile tile = new Models.Tile();
        //            tile.tileId = ctrTile.ImgId;
        //            Point cellPosition = ctrTile.TransformToAncestor(grid).Transform(new Point(0, 0));
        //            tile.rectPos = new Int32Rect((int)cellPosition.X, (int)cellPosition.Y, tileWidth, tileHeight);
        //            listTile.Add(tile);
        //        }
        //    }
        //    return listTile;
        //}
    }
}
