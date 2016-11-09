using System;
using System.ComponentModel;
using System.Windows;
using Microsoft.Win32;

namespace ggMapEditor.Views.Main
{
    /// <summary>
    /// Interaction logic for RootWindow.xaml
    /// </summary>
    public partial class RootWindow : Window
    {
        private Models.Combine combine;
        private Controls.MatrixGrid matrixGrid;

        public int Row
        {
            get { return TileMap.row; }
            set { RaisePropertyChanged("Row"); }
        }
        public int Column
        {
            get { return TileMap.column; }
            set { RaisePropertyChanged("Column"); }
        }
        private Models.TileMap TileMap
        {
            get { return combine.tileMap; }
            set
            {
                combine.tileMap = value;
            }
        }

        public event PropertyChangedEventHandler PropertyChanged;
        internal void RaisePropertyChanged(string property)
        {
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(property));
        }

        public RootWindow()
        {
            InitializeComponent();
            combine = new Models.Combine();
            DataContext = this;
        }

        private void SaveTileMap_Click(object sender, RoutedEventArgs e)
        {
            if (TileMap == null)
            {
                MessageBox.Show("Please create TileMap before create tileset.");
                return;
            }

            TileMap.listTile = matrixGrid.RetrieveTiles();
            Json.ConvertJson.SaveFile(combine);
            status.Content = "Save map";
        }

        private void OpenTileMap_Click(object sender, RoutedEventArgs e)
        {
            OpenFileDialog fileDialog = new OpenFileDialog();
            fileDialog.Multiselect = true;
            fileDialog.Filter = "Tile map files (*json)|*.json";
            fileDialog.InitialDirectory = Environment.GetFolderPath(Environment.SpecialFolder.MyDocuments);

            //if (fileDialog.ShowDialog() == true)
            //    fileName = fileDialog.FileName + ".tmx";
        }

        private void NewTileMap_Click(object sender, RoutedEventArgs e)
        {
            Dialogs.NewTileMapDialog fileDialog = new Dialogs.NewTileMapDialog();
            fileDialog.ShowDialog();
            if (fileDialog.GetCombine() != null)
            {
                combine = fileDialog.GetCombine();
                matrixGrid = new Controls.MatrixGrid();
                matrixGrid.ColumnCount = TileMap.column;
                matrixGrid.RowCount = TileMap.row;
                matrixGrid.TileSize = TileMap.leafWidth;
                matrixGrid.InitGrid();
                zoomBox.Children.Add(matrixGrid);
            }
        }

        private void NewTileSet_Click(object sender, RoutedEventArgs e)
        {
            if (TileMap == null)
            {
                MessageBox.Show("Please create TileMap before create tileset.");
                return;
            }
            Dialogs.AddTilesetDialog fileDialog = new Dialogs.AddTilesetDialog(combine.folderPath);
            fileDialog.ShowDialog();
            combine.tileset = fileDialog.GetTileset();
            //if (combine.tileset != null && combine.tileset.imageUri != null)
            //    tilesetBox.SetTileset(combine.tileset);
        }
    }
}
