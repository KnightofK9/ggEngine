using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using ggMapEditor.Commands;
using ggMapEditor.Helpers;

namespace ggMapEditor.ViewModels.Main
{
    class RootWindowViewModel : Base.BaseViewModel
    {
        #region Private Members
        private ObservableCollection<Models.Combine> combines;
        private DockManagerViewModel dockManagerViewModel;
        private int current;

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
            current = -1;
            combines = new ObservableCollection<Models.Combine>();

            dockManagerViewModel = new DockManagerViewModel();
            AddTabCommand = new RelayCommand(AddTab);
            AddTilesetCommand = new RelayCommand(AddTileset);
            SaveCommand = new RelayCommand(Save);
            ControlsCommand = new RelayCommand(SwitchControls);

            ToolsEventHandle.DrawTool = ToolTypes.Block;
        }
        #endregion


        #region Commands
        public RelayCommand AddTabCommand { get; set; }
        public RelayCommand AddTilesetCommand { get; set; }
        public RelayCommand SaveCommand { get; set; }
        public RelayCommand ControlsCommand { get; set; }
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
            current++;
        }

        private void AddTileset(object parameter)
        {
            if (combines.Count == 0 || combines[0] == null)
                return;

            Views.Dialogs.AddTilesetDialog dialog = new Views.Dialogs.AddTilesetDialog(combines[0].folderPath);
            dialog.ShowDialog();

            Models.Tileset tset = (dialog.DataContext as ViewModels.AddTilesetViewModel).GetTileset();
            if (tset == null) return;
            //check if tilesetKey is exist

            TilesetTapViewModel tsetTab = new TilesetTapViewModel(tset);
            tsetTab.Title = tset.id;
            DockManagerViewModel.AddAnchorTab(tsetTab);
            combines[current].tilesets.Add(tset);
        }

        private void Save(object parameter)
        {
            if (combines[current] == null)
            {
                MessageBox.Show("Please create TileMap before.");
                return;
            }
            combines[current].tileMap.listTile = (dockManagerViewModel.DockTabs[current] as MapAreaTabViewModel).ListTile;
            Json.ConvertJson.SaveFile(combines[current]);
            //status.Content = "Save map";
        }

        private void SwitchControls(object parameter)
        {
            switch ((parameter as Button).Name)
            {
                case "toolBlock":
                    ToolsEventHandle.DrawTool = ToolTypes.Block;
                    break;

                case "pen":
                    ToolsEventHandle.DrawTool = ToolTypes.Pen;
                    break;

                case "eraser":
                    ToolsEventHandle.DrawTool = ToolTypes.Eraser;
                    break;

                case "arrow":
                    ToolsEventHandle.DrawTool = ToolTypes.Arrow;
                    break;

                default:
                    return;
            }
        }
        #endregion
    }
}
