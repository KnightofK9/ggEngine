using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.IO;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Media;
using System.Windows.Media.Imaging;

namespace ggMapEditor.Views.Fragments
{
    /// <summary>
    /// Interaction logic for TilesetBox.xaml
    /// </summary>
    public partial class TilesetBox : UserControl//, INotifyPropertyChanged
    {
        private Models.Tileset tileset;

        public event PropertyChangedEventHandler PropertyChanged;
        internal void RaisePropertyChanged(string property)
        {
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(property));
        }
        public TilesetBox()
        {
            InitializeComponent();
            tileset = new Models.Tileset();
            CtrTiles = new ObservableCollection<Controls.Tile>();
            DataContext = this;
        }

        #region Properties
        public string TilesetName
        {
            get
            {
                return tileset.tilesetKey;
            }
            private set
            {
                RaisePropertyChanged("TilesetName");
            }
        }

        public Models.Tileset Tileset
        {
            get { return tileset; }
            set
            {
                tileset = value;
                RaisePropertyChanged("TilesetName");
            }
        }

        private ObservableCollection<Controls.Tile> ctrTiles;
        public ObservableCollection<Controls.Tile> CtrTiles
        {
            get { return ctrTiles; }
            set
            {
                ctrTiles = value;
                RaisePropertyChanged("CtrTiles");
            }
        }
        #endregion



        public void SetTileset(Models.Tileset tileset)
        {
            this.tileset = tileset;
            SplitCells();
        }

        #region Other functions
        private void SplitCells()
        {
            if (CtrTiles != null)
            {
                BitmapImage source = new BitmapImage(tileset.imageUri);

                foreach (var t in tileset.tileList)
                {
                    Controls.Tile tile = new Controls.Tile();
                    CroppedBitmap croppedBitmap = new CroppedBitmap(source, new Int32Rect(t.x, t.y, tileset.tileWidth, tileset.tileHeight));
                    tile.TileSource = croppedBitmap;
                    tile.TileWidth = tileset.tileWidth;
                    tile.TileHeight = tileset.tileHeight;
                    tile.ImgId = t.id;
                    CtrTiles.Add(tile);
                }
            }
        }
        #endregion


        //public TilesetBox(Models.Tileset tset)
        //{
        //    InitializeComponent();
        //    //tileset = tset;
        //    //CtrTiles = new ObservableCollection<Controls.Tile>();
        //    //DataContext = this;
        //    DataContext = new ViewModels.TilesetTapViewModel(tset);
        //}
    }
}
