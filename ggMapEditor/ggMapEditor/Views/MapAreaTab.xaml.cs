using System;
using System.Windows;
using System.Windows.Controls;

namespace ggMapEditor.Views
{
    public partial class MapAreaTab : UserControl
    {
        //public static readonly DependencyProperty ViewModelProperty = DependencyProperty.Register
        //    (
        //        "ViewModel",
        //        typeof(ViewModels.MapAreaTabViewModel),
        //        typeof(MapAreaTab),
        //        new PropertyMetadata()
        //    );
        //public ViewModels.MapAreaTabViewModel ViewModel
        //{
        //    get { return (ViewModels.MapAreaTabViewModel)GetValue(ViewModelProperty); }
        //    private set
        //    {
        //        if (value != null)
        //            (value as ViewModels.MapAreaTabViewModel).container = itemCtrl;
        //        SetValue(ViewModelProperty, value);
        //    }
        //}

        private ViewModels.MapAreaTabViewModel vm;  //to set viewmodel container

        public MapAreaTab()
        {
            InitializeComponent();
        }

        private void UserControl_DataContextChanged(object sender, DependencyPropertyChangedEventArgs e)
        {
            vm = e.NewValue as ViewModels.MapAreaTabViewModel;
            vm.container = itemCtrl;
        }
    }
}
