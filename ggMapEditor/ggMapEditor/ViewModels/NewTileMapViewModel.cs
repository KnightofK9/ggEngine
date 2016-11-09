using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using ggMapEditor.Commands;

namespace ggMapEditor.ViewModels
{
    class NewTileMapViewModel : Base.BaseViewModel
    {
        private Models.Combine combine;

        public RelayCommand OkCommand { get; set; }
        public RelayCommand CancelCommand { get; set; }
        public RelayCommand BrowseCommand { get; set; }

        public NewTileMapViewModel()
        {
            combine = new Models.Combine();
            combine.tileMap = new Models.TileMap();
            combine.folderPath = Environment.GetFolderPath(Environment.SpecialFolder.Desktop);

            OkCommand = new RelayCommand(OkButton_Click);
            CancelCommand = new RelayCommand(CancelButton_Click);
            BrowseCommand = new RelayCommand(BrowseButton_Click);

            RowCount = 10;
            ColumnCount = 10;
        }

        #region Properties
        public int RowCount
        {
            get { return TileMap.row; }
            set
            {
                TileMap.row = value;
                RaisePropertyChanged("MapPixels");
                RaisePropertyChanged("RowCount");
            }
        }
        public int ColumnCount
        {
            get { return TileMap.column; }
            set
            {
                TileMap.column = value;
                RaisePropertyChanged("MapPixels");
                RaisePropertyChanged("ColumnCount");
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
                RaisePropertyChanged("MapPixels");
            }
        }

        public string MapPixels
        {
            get
            {
                TileMap.mapHeight = TileMap.row * TileMap.leafWidth;
                TileMap.mapWidth = TileMap.column * TileMap.leafHeight;
                return TileMap.mapWidth + " x " + TileMap.mapHeight + " pixels";
            }
            set
            {
                RaisePropertyChanged("MapPixels");
            }
        }
        private Models.TileMap TileMap
        {
            get { return combine.tileMap; }
            set
            {
                combine.tileMap = value;
            }
        }
        public string FolderPath
        {
            get { return combine.folderPath; }
            set
            {
                combine.folderPath = value;
                RaisePropertyChanged("FolderPath");
            }
        }

        public string FolderName
        {
            get { return combine.folderName; }
            set
            {
                combine.folderName = value;
                RaisePropertyChanged("FolderName");
            }
        }

        #endregion

        #region Commands
        private void OkButton_Click(object parameter)
        {
            //Resize tilemap
            int max = Math.Max(TileMap.row, TileMap.column);
            double n = Math.Ceiling(Math.Log((double)max, 2.0));
            TileMap.height = TileMap.width = (int)Math.Pow(2.0, n) * TileSize;

            //Save folder contain tilemap
            combine.folderPath += "//" + FolderName;
            Json.ConvertJson.SaveFile(combine);
            base.CloseWindow();
        }
        private void CancelButton_Click(object parameter)
        {
            this.CloseWindow();
        }
        private void BrowseButton_Click(object parameter)
        {
            System.Windows.Forms.FolderBrowserDialog folderDialog = new System.Windows.Forms.FolderBrowserDialog();
            folderDialog.ShowNewFolderButton = true;
            var result = folderDialog.ShowDialog();
            if (result == System.Windows.Forms.DialogResult.OK)
            {
                FolderPath = folderDialog.SelectedPath;
            }
        }
        #endregion

        public Models.Combine GetCombine()
        {
            return combine;
        }

        public override void CloseWindow(Nullable<bool> result = true)
        {
            //combine = null;
          //GC.Collect();
            base.CloseWindow(result);
        }
    }
}
