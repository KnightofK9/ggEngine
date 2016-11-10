using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using ggMapEditor.Commands;
using ggMapEditor.Models;
using Microsoft.Win32;
using Newtonsoft.Json;
using ggMapEditor.Helpers;

namespace ggMapEditor.ViewModels
{
    class AddTilesetViewModel : Base.BaseViewModel
    {
        private Models.Tileset tileset;
        private string folderPath;

        public AddTilesetViewModel(string folderPath)
        {
            tileset = new Tileset();
            TileSize = 32;
            Name = "Tileset";
            this.folderPath = folderPath;
            OpenFileCommand = new RelayCommand(BrowsFile);
            OkCommand = new RelayCommand(ButtonOk);
            CancelCommand = new RelayCommand(ButtonCancel);
        }

        #region Properties
        public string Name
        {
            get { return tileset.id; }
            set
            {
                tileset.id = value;
                RaisePropertyChanged("Name");
            }

        }
        public TilesetType Type
        {
            get { return tileset.type; }
            set
            {
                tileset.type = value;
                RaisePropertyChanged("Type");
            }
        }
        public Uri ImageUri
        {
            get { return tileset.imageUri; }
            set
            {
                tileset.imageUri = value;
                RaisePropertyChanged("ImageUri");
            }
        }
        public int TileSize
        {
            get { return tileset.tileWidth; }
            set
            {
                tileset.height = value;
                tileset.width = value;

                if (value == 0)
                {
                    MessageBox.Show("Invalid value. Set default tile size is 32.");
                    tileset.height = tileset.width = 32;
                    RaisePropertyChanged("TileSize");
                }
            }
        }
        #endregion

        #region Commands
        public RelayCommand OpenFileCommand { get; set; }
        public RelayCommand OkCommand { get; set; }
        public RelayCommand CancelCommand { get; set; }

        void ButtonOk(object parameter)
        {
            if (!RenderTileset())
                this.CloseWindow();
            base.CloseWindow();
        }
        void ButtonCancel(object parameter)
        {
            CloseWindow();
        }
        void BrowsFile(object parameter)
        {
            OpenFileDialog fileDialog = new OpenFileDialog();
            fileDialog.Multiselect = true;
            fileDialog.Filter = "Image files |*png;*jpge;jpg";
            fileDialog.InitialDirectory = Environment.GetFolderPath(Environment.SpecialFolder.MyDocuments);

            if (fileDialog.ShowDialog() == true)
                try
                {
                    ImageUri = new Uri(fileDialog.FileName, UriKind.RelativeOrAbsolute);
                }
                catch (Exception ex)
                {
                    MessageBox.Show(ex.ToString());
                }

        }
        #endregion

        #region Other functions
        public Models.Tileset GetTileset()
        {
            return tileset;
        }

        private bool RenderTileset()
        {
            //Kiểm tra các tileset có lưu chồng lên nhau k
            string imgPath = folderPath + "\\" + tileset.id + ".png";
            if (File.Exists(imgPath))
            {
                MessageBox.Show("This name is exists. Please choose another.");
                return false;
            }

            StatusMsg = "Cropping Image...";
            BitmapImage img = new BitmapImage(tileset.imageUri);
            List<BitmapSource> bmCells = BitmapImageExtensions.CropImage(img, TileSize, TileSize);
            StatusMsg = "Cropped Image";

            for (int i = 0; i < bmCells.Count; i++)
            {
                Models.TilesetCell tile = new TilesetCell();
                tile.x = i* TileSize;
                tile.y = 0;
                tileset.tileList.Add(tile);
            }

            var newImgSource = bmCells.MergeImage();
            tileset.width = newImgSource.PixelWidth;
            tileset.height = newImgSource.PixelHeight;
            tileset.numberOfCell = bmCells.Count;
            tileset.numberOfCellPerRow = bmCells.Count;
            tileset.numberOfCellPerColumn = 1;

            newImgSource.SaveImage(imgPath);
            tileset.imageUri = new Uri(imgPath, UriKind.RelativeOrAbsolute);

            string jsonFilePath = folderPath + "\\" + tileset.id + ".json";
            string json = JsonConvert.SerializeObject(tileset);
            System.IO.File.WriteAllText(jsonFilePath, json);

            return true;
        }

        public override void CloseWindow(Nullable<bool> result = true)
        {
            //if (tileset != null)
            //{
            //    tileset.tileList.Clear();
            //    tileset = null;
            //}
            base.CloseWindow(result);
        }
        #endregion
    }
}
