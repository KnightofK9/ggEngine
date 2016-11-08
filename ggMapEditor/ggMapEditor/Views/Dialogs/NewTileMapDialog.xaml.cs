using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;

namespace ggMapEditor.Views.Dialogs
{
    /// <summary>
    /// Interaction logic for NewTileMap.xaml
    /// </summary>
    public partial class NewTileMapDialog : Window
    {
        ViewModels.NewTileMapViewModel vm;

        public NewTileMapDialog()
        {
            InitializeComponent();
            vm = new ViewModels.NewTileMapViewModel();
            this.DataContext = vm;
        }

        public Models.Combine GetCombine()
        {
            return vm.GetCombine();
        }
    }
}
