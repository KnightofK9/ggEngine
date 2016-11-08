using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;

namespace ggMapEditor.Helpers
{
    public static class DialogCloser
    {
        public static readonly DependencyProperty DialogResultProperty
            = DependencyProperty.RegisterAttached
            (
                "DialogResult",
                typeof(bool?),
                typeof(DialogCloser),
                new PropertyMetadata(DialogResultChanged)
            );
        private static void DialogResultChanged(DependencyObject sender, DependencyPropertyChangedEventArgs e)
        {
            var window = sender as Window;
            if (window != null)
                window.Close();
        }
        public static void SetDialogResult(Window window, bool? value)
        {
            window.SetValue(DialogResultProperty, value);
        }
    }
}
