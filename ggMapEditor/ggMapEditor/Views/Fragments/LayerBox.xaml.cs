using System.Collections.ObjectModel;
using System.Windows.Controls;

namespace ggMapEditor.Views.Fragments
{
    public partial class LayerBox : UserControl
    {
        private ViewModels.LayerBoxViewModel vm;
        public LayerBox()
        {
            InitializeComponent();
            vm = new ViewModels.LayerBoxViewModel();
            root.DataContext = vm;
        }

        public ObservableCollection<Models.Layer> GetListLayer()
        {
            return vm.Layers;
        }
    }
}
