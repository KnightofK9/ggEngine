using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Media.Imaging;
using ggMapEditor.Commands;
using ggMapEditor.Models;
using Microsoft.Win32;
using Newtonsoft.Json;

namespace ggMapEditor.ViewModels
{
    class LoadBackgroundViewModel : Base.BaseViewModel
    {
        #region Private members
        private string combinePath;
        private bool canCreate;
        private Models.TileMap tileMap;
        private Models.Tileset tileset;

        #endregion

        #region Properties
        public Rect TileViewPort
        {
            get { return new Rect(0, 0, tileMap.leafWidth, tileMap.leafHeight); }
        }
        public string MapSizeText
        {
            get
            {
                return "(row x column) : "
                    + tileMap.mapWidth.ToString()
                    + " x "
                    + tileMap.mapHeight.ToString();
            }
        }
        public int MapWidth
        {
            get { return tileMap.mapWidth; }
            set
            {
                tileMap.mapWidth = value;
                RaisePropertyChanged(nameof(MapSizeText));
            }
        }
        public int MapHeight
        {
            get { return tileMap.mapHeight; }
            set
            {
                tileMap.mapHeight = value;
                RaisePropertyChanged(nameof(MapSizeText));
            }
        }
        public int TileWidth
        {
            get { return tileMap.leafWidth; }
            set
            {
                tileMap.leafWidth = value;
                tileset.tileWidth = value;
                RaisePropertyChanged(nameof(TileWidth));
            }
        }
        public Uri ImageUri
        {
            get { return tileset.imageUri; }
            set
            {
                tileset.imageUri = value;
                RaisePropertyChanged(nameof(ImageUri));
            }
        }
        public string Name
        {
            //get { return ; }
            set
            {
                tileset.id = value;
                tileMap.id = value;
                RaisePropertyChanged(nameof(Name));
            }
        }
        public int TileHeight
        {
            get { return tileMap.leafHeight; }
            set
            {
                tileMap.leafHeight = tileset.tileHeight = value;
                RaisePropertyChanged(nameof(TileHeight));
            }
        }
        //public int ColumnCount
        //{
        //    get { return columnCount; }
        //    set
        //    {
        //        columnCount = value;
        //        RaisePropertyChanged(nameof(ColumnCount));
        //    }
        //}
        //public int RowCount
        //{
        //    get { return rowCount; }
        //    set
        //    {
        //        rowCount = value;
        //        RaisePropertyChanged(nameof(RowCount));
        //    }
        //}
        #endregion

        #region Constructors
        public LoadBackgroundViewModel(string combinePath)
        {
            this.combinePath = combinePath;
            tileMap = new Models.TileMap();
            tileset = new Models.Tileset();

            OkCommand = new RelayCommand(ButtonOK_Click);
            CancelCommand = new RelayCommand(ButtonCancel_Click);
            OpenFileCommand = new RelayCommand(BrowserButton_Click);
        }
        #endregion

        #region Commands
        public RelayCommand OkCommand { get; set; }
        public RelayCommand CancelCommand { get; set; }
        public RelayCommand OpenFileCommand { get; set; }
        #endregion

        #region Events

        #endregion

        #region Others
        private void ButtonOK_Click(object parameter)
        {

        }
        private void ButtonCancel_Click(object parameter)
        {

        }
        private void BrowserButton_Click(object parameter)
        {
            ShowOpenFileDialog();
            if (tileset.imageUri == null || !RenderTileset())
            {
                canCreate = false;
                return;
            }

            
        }

        public override void CloseWindow(Nullable<bool> isSaveRecord = false)
        {
            tileset = null;
            tileset.tileList.Clear();
            tileMap = null;
            tileMap.listTile.Clear();

            base.CloseWindow(false);
        }


        private void ShowOpenFileDialog()
        {
            OpenFileDialog fileDialog = new OpenFileDialog();
            fileDialog.Multiselect = true;
            fileDialog.Filter = "Image files |*png;*jpge;*jpg";
            fileDialog.InitialDirectory = Environment.GetFolderPath(Environment.SpecialFolder.Favorites);

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
        private bool RenderTileset()
        {
            //Kiểm tra các tileset có lưu chồng lên nhau k
            string imgPath = combinePath + "\\" + tileset.id + ".png";
            string tileMapPath = combinePath + "\\" + tileMap.id + ".json";
            if (File.Exists(imgPath) || File.Exists(tileMapPath))
            {
                MessageBox.Show("This name is exists. Please choose another.");
                return false;
            }

            BitmapImage img = new BitmapImage(tileset.imageUri);
            List<ImageCell> bmCells = this.CropImage(img, TileWidth, TileHeight);
            var sourceCells = new List<BitmapSource>();
            for (int i = 0; i < bmCells.Count; i++)
            {
                Models.TilesetCell tile = new TilesetCell();
                tile.x = i * TileWidth;
                tile.y = 0;
                tileset.tileList.Add(tile);
                sourceCells.Add(bmCells[i].source);
            }

            var newImgSource = sourceCells.MergeImage();
            tileset.width = newImgSource.PixelWidth;
            tileset.height = newImgSource.PixelHeight;
            tileset.numberOfCell = bmCells.Count;
            tileset.numberOfCellPerRow = 1;
            tileset.numberOfCellPerColumn = bmCells.Count;

            newImgSource.SaveImage(imgPath);
            tileset.imageUri = new Uri(imgPath, UriKind.RelativeOrAbsolute);

            string jsonFilePath = combinePath + "\\" + tileset.id + ".json";
            string json = JsonConvert.SerializeObject(tileset);
            System.IO.File.WriteAllText(jsonFilePath, json);

            return true;
        }

        public List<ImageCell> CropImage(BitmapImage img, int cellWidth = 32, int cellHeight = 32)
        {
            var imgCell = new List<ImageCell>();
            var hashMap = new Dictionary<long, List<ImageCell>>();

            if (img != null && cellWidth > 0 && cellHeight > 0)
            {
                int width = img.PixelWidth;
                int height = img.PixelHeight;

                for (int i = 0; i <= height - cellHeight; i += cellHeight)
                    for (int k = 0; k <= width - cellWidth; k += cellWidth)
                    {
                        Int32Rect rect = new Int32Rect(k, i, cellWidth, cellHeight);
                        CroppedBitmap croppedBitmap = new CroppedBitmap(img, rect);
                        long key = croppedBitmap.ToBytes().SumBytes();
                        List<ImageCell> list;
                        if (hashMap.TryGetValue(key, out list))
                        {
                            bool isExist = false;
                            foreach (var item in list)
                                if (croppedBitmap.IsEqual(item.source))
                                {
                                    isExist = true;
                                    break;
                                }
                            if (isExist == false)
                            {
                                hashMap[key].Add(croppedBitmap);
                                imgCell.Add(croppedBitmap);
                            }
                        }
                        else
                        {
                            list = new List<BitmapSource>();
                            list.Add(croppedBitmap);
                            hashMap.Add(key, list);
                            imgCell.Add(croppedBitmap);
                        }
                    }
            }
            return imgCell;
        }
        #endregion

        private class ImageCell
        {
            public BitmapSource source;
            public Point position;
        }
    }
}
