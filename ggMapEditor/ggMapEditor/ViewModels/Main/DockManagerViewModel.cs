using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Controls;
using ggMapEditor.Commands;

namespace ggMapEditor.ViewModels.Main
{
    class DockManagerViewModel : Base.BaseViewModel
    {
        #region Properties
        private ObservableCollection<DockTabViewModel> dockTabs;
        public ObservableCollection<DockTabViewModel> DockTabs
        {
            get { return dockTabs; }
            set
            {
                dockTabs = value;
                RaisePropertyChanged(nameof(DockTabs));
            }
        }

        public ObservableCollection<object> Anchorables { get; private set; }
        #endregion

        #region Constructors
        public DockManagerViewModel()
        {
            this.DockTabs = new ObservableCollection<DockTabViewModel>();
            this.Anchorables = new ObservableCollection<object>();
        }
        #endregion


        #region Other Funcs
        public void AddDockTab(DockTabViewModel tab)
        {
            tab.PropertyChanged += DockWindowViewModel_PropertyChanged;
            if (!tab.IsClosed)
                DockTabs.Add(tab);
        }
        public void AddAnchorTab(AnchorTabViewModel tab)
        {
            Anchorables.Add(tab);
        }
        #endregion


        private void DockWindowViewModel_PropertyChanged(object sender, PropertyChangedEventArgs e)
        {
            DockTabViewModel documnet = sender as DockTabViewModel;
            if (e.PropertyName == nameof(DockTabViewModel.IsClosed))
            {
                if (documnet.IsClosed)
                    this.DockTabs.Remove(documnet);
                else
                    this.DockTabs.Add(documnet);
            }
        }
    }
}
