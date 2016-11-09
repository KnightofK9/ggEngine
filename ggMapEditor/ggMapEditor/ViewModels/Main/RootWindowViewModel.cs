using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using ggMapEditor.Commands;

namespace ggMapEditor.ViewModels.Main
{
    class RootWindowViewModel : Base.BaseViewModel
    {
        #region Private Members
        private ObservableCollection<Models.Combine> combines;
        //private ObservableCollection<Models.TileMap> tileMaps;
        private DockManagerViewModel dockManagerViewModel;

        #endregion

        #region Properties
        //private Models.TileMap
        public DockManagerViewModel DockManagerViewModel
        {
            get { return dockManagerViewModel; }
            set
            {
                dockManagerViewModel = value;
                RaisePropertyChanged("DockManagerViewModel");
            }
        }
        //public MenuItemViewModel menuItemViewModel{get; private set;}
        //public ToolBarViewModel toolBarViewModel{get; private set;}
        //public StatusBarViewModel statusBarViewModel{get; private set;}


        #endregion

        #region Constructors

        public RootWindowViewModel()
        {
            combines = new ObservableCollection<Models.Combine>();

            dockManagerViewModel = new DockManagerViewModel();
            AddTabCommand = new RelayCommand(AddTab);
            AddTilesetCommand = new RelayCommand(AddTileset);
            SaveCommand = new RelayCommand(Save);
        }
        #endregion


        #region Commands
        public RelayCommand AddTabCommand { get; set; }
        public RelayCommand AddTilesetCommand { get; set; }
        public RelayCommand SaveCommand { get; set; }
        #endregion

        #region Other Funcs
        private void AddTab(object parameter)
        {
            Views.Dialogs.NewTileMapDialog dialog = new Views.Dialogs.NewTileMapDialog();
            dialog.ShowDialog();
            Models.Combine cmb = (dialog.DataContext as ViewModels.NewTileMapViewModel).GetCombine();
            if (cmb == null || cmb.tileMap == null)
                return;

            MapAreaTabViewModel mapTab = new MapAreaTabViewModel(cmb.tileMap);
            mapTab.Title = cmb.folderName;
            DockManagerViewModel.AddDockTab(mapTab);

            combines.Add(cmb);
        }

        private void AddTileset(object parameter)
        {
            if (combines.Count == 0 || combines[0] == null)
                return;
            
            Views.Dialogs.AddTilesetDialog dialog = new Views.Dialogs.AddTilesetDialog(combines[0].folderPath);
            dialog.ShowDialog();
            Models.Tileset tset = (dialog.DataContext as ViewModels.AddTilesetViewModel).GetTileset();
            if (tset == null || tset.imageUri == null)
                return;

            TilesetTapViewModel tsetTab = new TilesetTapViewModel(tset);
            tsetTab.Title = "Tileset";
            DockManagerViewModel.AddAnchorTab(tsetTab);
        }

        private void Save(object parameter)
        {
            if (combines[0] == null)
            {
                MessageBox.Show("Please create TileMap before.");
                return;
            }

        //    combines[0].tileMap.listTile = dockManagerViewModel.DockTabs[0].RetrieveTiles();
        //    Json.ConvertJson.SaveFile(combine);
        //    status.Content = "Save map";
        }
        #endregion
    }
}
