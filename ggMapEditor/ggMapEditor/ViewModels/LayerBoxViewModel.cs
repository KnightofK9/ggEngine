using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using ggMapEditor.Commands;

namespace ggMapEditor.ViewModels
{
    class LayerBoxViewModel : Base.BaseViewModel
    {
        private ObservableCollection<Models.Layer> layers;
        public ObservableCollection<Models.Layer> Layers
        {
            get { return layers; }
            set
            {
                layers = value;
                RaisePropertyChanged("Layers");
            }
        }

        public LayerBoxViewModel()
        {
            Layers = new ObservableCollection<Models.Layer>();

            AddLayerCommand = new RelayCommand(AddLayer);
            DeleteLayerCommand = new RelayCommand(DeleteLayer);
        }

        #region Commands
        public RelayCommand AddLayerCommand { get; set; }
        public RelayCommand DeleteLayerCommand { get; set; }
        public RelayCommand DupplicateCommand { get; set; }


        private void AddLayer(object parameter)
        {
            Layers.Add(new Models.Layer());
        }
        private void DeleteLayer(object parameter)
        {

        }

        #endregion
    }
}
