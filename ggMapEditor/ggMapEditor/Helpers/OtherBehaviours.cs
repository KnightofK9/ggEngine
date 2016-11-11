using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Controls.Primitives;
using System.Windows.Input;

namespace ggMapEditor.Helpers
{
    class OtherBehaviours
    {
        #region SelectionChanged
        public static readonly DependencyProperty SelectionChangedCommandProperty =
            DependencyProperty.RegisterAttached("SelectionChangedCommand", typeof(ICommand), typeof(MouseBehaviour), new FrameworkPropertyMetadata(new PropertyChangedCallback(SelectionChangedCommandChanged)));

        private static void SelectionChangedCommandChanged(DependencyObject d, DependencyPropertyChangedEventArgs e)
        {
            Selector selector = (Selector)d;

            if (selector != null)
            {
                selector.SelectionChanged += new SelectionChangedEventHandler(selector_SelectionChanged);
            }
        }

        static void selector_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            Selector selector = (Selector)sender;

            if (selector != null)
            {
                ICommand command = selector.GetValue(SelectionChangedCommandProperty) as ICommand;

                if (command != null)
                {
                    command.Execute(e);
                }
            }
        }

        public static void SetSelectionChangedCommand(UIElement element, ICommand value)
        {
            element.SetValue(SelectionChangedCommandProperty, value);
        }

        public static ICommand GetSelectionChangedCommand(UIElement element)
        {
            return (ICommand)element.GetValue(SelectionChangedCommandProperty);
        }
        #endregion

    }
}
