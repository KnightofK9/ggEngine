using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Drawing;
using System.Drawing.Imaging;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Interop;
using System.Windows.Media.Imaging;
using ggMapEditor.Commands;
using ggMapEditor.Helpers;

namespace ggMapEditor.ViewModels.Main
{
    class RootWindowViewModel : Base.BaseViewModel
    {
        #region Private Members
        private Models.Combine combine;
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
            //combines = new ObservableCollection<Models.Combine>();

            dockManagerViewModel = new DockManagerViewModel();
            AddTabCommand = new RelayCommand(AddTab);
            AddTilesetCommand = new RelayCommand(AddTileset);
            SaveCommand = new RelayCommand(Save);
            ControlsCommand = new RelayCommand(SwitchControls);
            CaptureImgCommand = new RelayCommand(CaptureImage);
            LoadBackgroundCommand = new RelayCommand(LoadBackground);

            //Static
            ToolsEventHandle.DrawTool = ToolTypes.Block;
            CacheElementCollection.Elements = new Dictionary<System.Windows.Point, UIElement>();

            StatusMsg = "Ready";
        }
        #endregion


        #region Commands
        public RelayCommand AddTabCommand { get; set; }
        public RelayCommand AddTilesetCommand { get; set; }
        public RelayCommand SaveCommand { get; set; }
        public RelayCommand ControlsCommand { get; set; }
        public RelayCommand CaptureImgCommand { get; set; }
        public RelayCommand LoadBackgroundCommand { get; set; }
        #endregion

        #region Other Funcs
        private void AddTab(object parameter)
        {
            Views.Dialogs.NewTileMapDialog dialog = new Views.Dialogs.NewTileMapDialog();
            dialog.ShowDialog();
            Models.Combine cmb = (dialog.DataContext as ViewModels.NewTileMapViewModel).GetCombine();
            if (cmb == null || cmb.tileMaps == null || cmb.tileMaps.Count == 0)
                return;

            MapAreaTabViewModel mapTab = new MapAreaTabViewModel(cmb.tileMaps[0]);
            mapTab.Title = cmb.folderName;
            DockManagerViewModel.AddDockTab(mapTab);

            combine = cmb;
            current++;

            StatusMsg = "Created " + cmb.folderName;
        }

        private void AddTileset(object parameter)
        {
            if (combine == null)
                return;

            Views.Dialogs.AddTilesetDialog dialog = new Views.Dialogs.AddTilesetDialog(combine.folderPath);
            var vm = dialog.DataContext as ViewModels.AddTilesetViewModel;
            vm.StatusMsgChanged += RootWindow_StatusMsgChanged;
            dialog.ShowDialog();
            
            Models.Tileset tset = vm.GetTileset();
            if (tset == null) return;

            TilesetTapViewModel tsetTab = new TilesetTapViewModel(tset);
            tsetTab.Title = tset.id;
            DockManagerViewModel.AddAnchorTab(tsetTab);
            combine.tilesets.Add(tset);

            StatusMsg = "Created " + tset.id;
        }

        private void Save(object parameter)
        {
            if (combine == null)
            {
                MessageBox.Show("Please create TileMap before.");
                StatusMsg = "";
                return;
            }
            if (combine.tileMaps.Count == 0)
                return;
            combine.tileMaps[current].listTile = (dockManagerViewModel.DockTabs[current] as MapAreaTabViewModel).HashMapChild;
            Json.ConvertJson.SaveFile(combine, current);
            StatusMsg = "Saved";
        }

        private void SwitchControls(object parameter)
        {
            switch ((parameter as Button).Name)
            {
                case "toolBlock":
                    ToolsEventHandle.DrawTool = ToolTypes.Block;
                    StatusMsg = "Using Block tool";
                    break;

                case "pen":
                    ToolsEventHandle.DrawTool = ToolTypes.Pen;
                    StatusMsg = "Using Pen tool";
                    break;

                case "eraser":
                    ToolsEventHandle.DrawTool = ToolTypes.Eraser;
                    StatusMsg = "Using Eraser tool";
                    break;

                case "arrow":
                    ToolsEventHandle.DrawTool = ToolTypes.Arrow;
                    StatusMsg = "Using Arrow tool";
                    break;

                default:
                    return;
            }
        }

        private void RootWindow_StatusMsgChanged(object sender, MessageEventArgs e)
        {
            StatusMsg = e.statusMsg;
        }

        protected override void SetStatusMsgChanged(MessageEventArgs e)
        {
            base.SetStatusMsgChanged(e);
            RaisePropertyChanged(nameof(StatusMsg));
        }

        private void CaptureImage(object parameter)
        {
            var mapAreaVM = DockManagerViewModel.DockTabs[current] as MapAreaTabViewModel;
            var image = mapAreaVM.CaptureImage();
            image.SaveImage(combine.folderPath + "\\" + combine.folderName + "_Captured.png");
        }

        private void LoadBackground(object parameter)
        {
            
        }
        #endregion
    }
}
