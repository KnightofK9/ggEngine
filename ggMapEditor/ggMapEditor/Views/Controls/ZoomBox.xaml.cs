using System;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;
using System.Windows.Markup;
using System.Windows.Media;

namespace ggMapEditor.Views.Controls
{
    /// <summary>
    /// Interaction logic for ZoomBox.xaml
    /// </summary>
    [ContentProperty(nameof(Children))]
    public partial class ZoomBox : UserControl
    {
        Nullable<Point> lastMousePositionOnTarget;
        Nullable<Point> lastCenterPositionOnTarget;
        Nullable<Point> lastDragedPoint;

        /// <summary>
        /// int tileSize;
        /// bool gridVisible;
        /// Rectangle viewPort;
        /// </summary>

        public static readonly DependencyPropertyKey ChildrenProperty = DependencyProperty.RegisterReadOnly
        (
            nameof(Children),
            typeof(UIElementCollection),
            typeof(ZoomBox),
            new PropertyMetadata()
        );

        public UIElementCollection Children
        {
            get { return (UIElementCollection)GetValue(ChildrenProperty.DependencyProperty); }
            private set { SetValue(ChildrenProperty, value); }
        }

        public ZoomBox()
        {
            InitializeComponent();

            scrollViewer.ScrollChanged += OnScrollViewerScrollChanged;
            scrollViewer.MouseLeftButtonUp += OnMouseLeftButtonUp;
            scrollViewer.PreviewMouseLeftButtonUp += OnMouseLeftButtonUp;
            scrollViewer.PreviewMouseWheel += OnPreviewMouseWheel;
            scrollViewer.PreviewMouseLeftButtonDown += OnMouseLeftButtonDown;
            scrollViewer.MouseMove += OnMouseMove;

            slider.ValueChanged += OnSliderValueChanged;

            Children = container.Children;
        }

        private void OnSliderValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e)
        {
            if (Helpers.ToolsEventHandle.DrawTool != ToolTypes.Arrow)
                return;

            scaleTransform.ScaleX = e.NewValue;
            scaleTransform.ScaleY = e.NewValue;

            Point centerViewport = new Point(scrollViewer.ViewportWidth / 2, scrollViewer.ViewportHeight / 2);
            lastCenterPositionOnTarget = scrollViewer.TranslatePoint(centerViewport, container);
        }

        void OnMouseMove(object sender, MouseEventArgs e)
        {
            if (Helpers.ToolsEventHandle.DrawTool != ToolTypes.Arrow)
                return;

            if (lastDragedPoint.HasValue)
            {
                Point posCurrent = e.GetPosition(scrollViewer);

                double distanceX = posCurrent.X - lastDragedPoint.Value.X;
                double distanceY = posCurrent.Y - lastDragedPoint.Value.Y;

                scrollViewer.ScrollToHorizontalOffset(scrollViewer.HorizontalOffset - distanceX);
                scrollViewer.ScrollToVerticalOffset(scrollViewer.VerticalOffset - distanceY);

                lastDragedPoint = posCurrent;
            }
        }

        void OnMouseLeftButtonDown(object sender, MouseButtonEventArgs e)
        {
            if (Helpers.ToolsEventHandle.DrawTool != ToolTypes.Arrow)
                return;

            var mousePos = e.GetPosition(scrollViewer);
            if (mousePos.X <= scrollViewer.ViewportWidth
                && mousePos.Y <= scrollViewer.ViewportHeight)
            {
                scrollViewer.Cursor = Cursors.ScrollAll;
                lastDragedPoint = mousePos;
                Mouse.Capture(scrollViewer);
            }
        }

        void OnPreviewMouseWheel(object sender, MouseWheelEventArgs e)
        {
            if (Helpers.ToolsEventHandle.DrawTool != ToolTypes.Arrow)
                return;

            lastMousePositionOnTarget = Mouse.GetPosition(container);

            if (e.Delta > 0)
                slider.Value++;
            if (e.Delta < 0)
                slider.Value--;

            e.Handled = true;
        }

        void OnMouseleftButtonUp(object sender, MouseButtonEventArgs e)
        {
            if (Helpers.ToolsEventHandle.DrawTool != ToolTypes.Arrow)
                return;

            scrollViewer.Cursor = Cursors.Arrow;
            scrollViewer.ReleaseMouseCapture();
            lastDragedPoint = null;
        }

        void OnScrollViewerScrollChanged(object sender, ScrollChangedEventArgs e)
        {
            if (Helpers.ToolsEventHandle.DrawTool != ToolTypes.Arrow)
                return;

            if (e.ExtentHeightChange != 0 || e.ExtentWidthChange != 0)
            {
                Nullable<Point> targetBeffore = null;
                Nullable<Point> targetCurrent = null;

                if (!lastMousePositionOnTarget.HasValue)
                {
                    if (lastCenterPositionOnTarget.HasValue)
                    {
                        Point centerOnTargetCurrent = scrollViewer.TranslatePoint(new Point(scrollViewer.ViewportWidth / 2,
                            scrollViewer.ViewportHeight / 2), container);
                        targetBeffore = lastCenterPositionOnTarget;
                        targetCurrent = centerOnTargetCurrent;
                    }
                }
                else
                { 
                    targetBeffore = lastMousePositionOnTarget;
                    targetCurrent = Mouse.GetPosition(container);

                    lastMousePositionOnTarget = null;
                }
                if (targetBeffore.HasValue)
                {
                    double targetPixelX = targetCurrent.Value.X - targetBeffore.Value.X;
                    double targetPixelY = targetCurrent.Value.Y - targetBeffore.Value.Y;

                    double multiplicatorX = e.ExtentWidth / container.Width;
                    double multiplicatorY = e.ExtentHeight / container.Height;

                    double newOffsetX = scrollViewer.HorizontalOffset - targetPixelX * multiplicatorX;
                    double newOffsetY = scrollViewer.VerticalOffset - targetPixelY * multiplicatorY;

                    if (double.IsNaN(newOffsetX) || double.IsNaN(newOffsetY))
                        return;

                    scrollViewer.ScrollToHorizontalOffset(newOffsetX);
                    scrollViewer.ScrollToVerticalOffset(newOffsetY);
                }
            }
        }

        void OnMouseLeftButtonUp(object sender, MouseButtonEventArgs e)
        {
            if (Helpers.ToolsEventHandle.DrawTool != ToolTypes.Arrow)
                return;

            scrollViewer.Cursor = Cursors.Arrow;
            scrollViewer.ReleaseMouseCapture();
            lastDragedPoint = null;
        }
    }
}
