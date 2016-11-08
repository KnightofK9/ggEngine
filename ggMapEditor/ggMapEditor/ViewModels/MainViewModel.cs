using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using ggMapEditor.Commands;
using Microsoft.Win32;
using Newtonsoft.Json;

namespace ggMapEditor.ViewModels
{
    class MainViewModel : Base.BaseViewModel
    {
        public Models.Combine combine { get; set; }
        public int MapWidth
        {
            get { return TileMap.mapWidth; }
            set
            {
                TileMap.mapWidth = value;
                RaisePropertyChanged("MapWidth");
            }
        }
        public int MapHeight
        {
            get { return TileMap.mapHeight; }
            set
            {
                TileMap.mapHeight = value;
                RaisePropertyChanged("MapHeigth");
            }
        }
        public int TileSize
        {
            get { return TileMap.leafWidth; }
            set
            {
                TileMap.leafWidth = value;
                TileMap.leafHeight = value;
                RaisePropertyChanged("TileSize");
            }
        }

        public Models.TileMap TileMap
        {
            get { return combine.tileMap; }
            set { combine.tileMap = value; }
        }

        public Models.Tileset Tileset
        {
            get { return combine.tileset; }
            set
            {
                combine.tileset = value;
                RaisePropertyChanged("Tileset");
            }
        }
        //public ObservableCollection<Models.Layer> layers
        //{
        //    get { return combine.layers; }
        //    set
        //    {
        //        combine.layers = value;
        //        RaisePropertyChanged("Layers");
        //    }
        //}

        public MainViewModel()
        {
            combine = new Models.Combine();
            SaveTileMapCommand = new RelayCommand(SaveTileMap);
            //NewTileSetCommand = new RelayCommand(NewTileset);
        }

        public RelayCommand SaveTileMapCommand { get; set; }
        public RelayCommand NewTileSetCommand { get; set; }

        private void SaveTileMap(object parameter)
        {
            SaveFileDialog fileDialog = new SaveFileDialog();
            fileDialog.Filter = "Tile map files|*json";
            fileDialog.InitialDirectory = Environment.GetFolderPath(Environment.SpecialFolder.MyDocuments);

            fileDialog.FileName = "untitled.json";
            if (fileDialog.ShowDialog() == true)
            {
                string json = JsonConvert.SerializeObject(combine);
                System.IO.File.WriteAllText(fileDialog.FileName, json);
            }
        }
        //private void NewTileset(object parameter)
        //{
        //    Views.Dialogs.AddTilesetDialog fileDialog = new Views.Dialogs.AddTilesetDialog();
        //    fileDialog.ShowDialog();
        //    //tilesetBox.Tiles = fileDialog.GetTiles();
        //    combine.tileset = fileDialog.GetTileset();
        //}
    }
}
