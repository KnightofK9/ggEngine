using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
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
        }
        #endregion


        #region Commands
        public RelayCommand AddTabCommand { get; set; }
        public RelayCommand AddTilesetCommand { get; set; }
        #endregion

        #region Other Funcs
        public void AddTab(object parameter)
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

        public void AddTileset(object parameter)
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
        #endregion
    }
}
