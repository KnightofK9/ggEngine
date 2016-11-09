using System.Collections.ObjectModel;
using System.Diagnostics;
using System.Linq;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Media;

namespace ggMapEditor.Views.Controls
{
    /// <summary>
    /// Interaction logic for MatrixGrid.xaml
    /// </summary>
    public partial class MatrixGrid : UserControl
    {
        private ObservableCollection<DragableLayout> listCellHasChild;


        public static readonly DependencyProperty RownCountProperty
            = DependencyProperty.Register("RowCount", typeof(int), typeof(MatrixGrid),
                new FrameworkPropertyMetadata(new PropertyChangedCallback(OnRowCountChanged)));
        public static readonly DependencyProperty ColumnCountProperty
            = DependencyProperty.Register("ColumnCount", typeof(int), typeof(MatrixGrid),
                new FrameworkPropertyMetadata(new PropertyChangedCallback(OnColumnCountChanged)));
        public static readonly DependencyProperty TileSizeProperty
            = DependencyProperty.Register("TileSize", typeof(int), typeof(MatrixGrid),
                new FrameworkPropertyMetadata(new PropertyChangedCallback(OnTileSizeChanged)));

        #region Constructors
        public MatrixGrid()
        {
            InitializeComponent();
            DataContext = this;
            listCellHasChild = new ObservableCollection<DragableLayout>();
        }
        #endregion

        #region Properties
        public int RowCount
        {
            get { return (int)GetValue(RownCountProperty); }
            set { SetValue(RownCountProperty, value); }
        }
        public int ColumnCount
        {
            get { return (int)GetValue(ColumnCountProperty); }
            set {   SetValue(ColumnCountProperty, value); }
        }
        public int TileSize
        {
            get { return (int)GetValue(TileSizeProperty); }
            set { SetValue(TileSizeProperty, value);}
        }
        public Rect TileViewPort
        {
            get { return new Rect(0,0,TileSize,TileSize); }
        }
        #endregion

        #region Callbacks
        private static void OnRowCountChanged(DependencyObject sender, DependencyPropertyChangedEventArgs e)
        {
            MatrixGrid matrixGrid = (MatrixGrid)sender;
            matrixGrid.RowCount = (int)e.NewValue;

        }
        private static void OnColumnCountChanged(DependencyObject sender, DependencyPropertyChangedEventArgs e)
        {
            MatrixGrid matrixGrid = (MatrixGrid)sender;
            matrixGrid.ColumnCount = (int)e.NewValue;
        }
        private static void OnTileSizeChanged(DependencyObject sender, DependencyPropertyChangedEventArgs e)
        {
            MatrixGrid matrixGrid = (MatrixGrid)sender;
            matrixGrid.TileSize = (int)e.NewValue;
        }
        #endregion

        public void InitGrid()
        {
            if (TileSize == 0 || RowCount == 0 | ColumnCount == 0)
                return;

            // Clean grid
            grid.Children.Clear();
            grid.ColumnDefinitions.Clear();
            grid.RowDefinitions.Clear();

            // Init grid
            grid.Width = TileSize * ColumnCount;
            grid.Height = TileSize * RowCount;

            // Create collumns, rows
            for (int i = 0; i < RowCount; i++)
                grid.RowDefinitions.
                    Add(new RowDefinition(){ Height = new GridLength(TileSize)});
            for (int i = 0; i < ColumnCount; i++)
                grid.ColumnDefinitions.
                    Add(new ColumnDefinition() { Width = new GridLength(TileSize) });

            // Add Cells
            for (int i = 0; i < RowCount; i++)
                for (int k = 0; k < ColumnCount; k++)
                {
                    DragableLayout layout = new DragableLayout();
                    //layout.id = QuadTree.QuadTree.GetPositionQuadTree(new System.Drawing.Point((int)(i*TileSize), (int)(k*TileSize)), grid as Panel);
                    grid.Children.Add(layout);
                    Grid.SetRow(layout, i);
                    Grid.SetColumn(layout, k);
                    //listCellHasChild.Add(layout);
                }
        }

        public ObservableCollection<Models.Tile> RetrieveTiles()
        {
            ObservableCollection<Models.Tile> listTile = new ObservableCollection<Models.Tile>();
            foreach (var cell in grid.Children)
            { 
                var childrens = (cell as DragableLayout).ListChild;
                if (childrens.Count > 0)
                {
                    Controls.Tile ctrTile = childrens.First() as Controls.Tile;
                    Models.Tile tile = new Models.Tile();
                    tile.tileId = ctrTile.ImgId;
                    Point cellPosition = ctrTile.TransformToAncestor(grid).Transform(new Point(0, 0));
                    tile.rectPos = new Int32Rect((int)cellPosition.X, (int)cellPosition.Y, TileSize, TileSize);
                    listTile.Add(tile);
                }
            }
            return listTile;
        }
    }
}
