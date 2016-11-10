﻿using System.Collections.ObjectModel;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;
using System.Windows.Markup;
using System.Windows.Media;
using System.Windows.Shapes;
using ggMapEditor.Helpers;

namespace ggMapEditor.Views.Controls
{
    public class DragableLayoutChildEventArgs
    {
        public readonly Models.Tile child;
        public readonly bool isCollidedObject;
        public DragableLayoutChildEventArgs(Models.Tile child)
        {
            this.child = child;
        }
        public DragableLayoutChildEventArgs(bool isCollidedObject)
        {
            this.isCollidedObject = isCollidedObject;
        }
    }

    [ContentProperty(nameof(Children))]
    public partial class DragableLayout : UserControl
    {
        public delegate void AddChildHandle(object sender, DragableLayoutChildEventArgs e);
        public event AddChildHandle ChildChanged;
        public event AddChildHandle CollidedChanged;

        public ObservableCollection<UIElement> ListChild { get; private set; }
        public static readonly DependencyPropertyKey ChildrenProperty = DependencyProperty.RegisterReadOnly
        (
            nameof(Children),
            typeof(UIElementCollection),
            typeof(DragableLayout),
            new PropertyMetadata()
        );

        public UIElementCollection Children
        {
            get { return (UIElementCollection)GetValue(ChildrenProperty.DependencyProperty); }
            private set { SetValue(ChildrenProperty, value); }
        }

        public DragableLayout()
        {
            InitializeComponent();
            ListChild = new ObservableCollection<UIElement>();
            
        }

        private void Layout_DragOver(object sender, DragEventArgs e)
        {
            if (e.Data.GetDataPresent("Object"))
                e.Effects = DragDropEffects.Copy;
            else
                e.Effects = DragDropEffects.None;

        }

        private void Layout_Drop(object sender, DragEventArgs e)
        {
            if (e.Handled == false && ListChild.Count == 0)
            {
                Canvas panel = (Canvas)sender;
                UIElement element = (UIElement)e.Data.GetData("Object");

                if (panel != null && element != null)
                {
                    DependencyObject parent = VisualTreeHelper.GetParent(element);
                    if (parent != null)
                    {
                        if (e.AllowedEffects.HasFlag(DragDropEffects.Copy))
                        {
                            Views.Controls.Tile cTile = new Views.Controls.Tile(element as Controls.Tile);
                            cTile.TilesetKey = (string)e.Data.GetData(nameof(cTile.TilesetKey));
                            cTile.ImgId = (long)e.Data.GetData(nameof(cTile.ImgId));
                            panel.Children.Add(cTile);
                            ListChild.Add(cTile);
                            e.Effects = DragDropEffects.Copy;


                            Models.Tile mTile = new Models.Tile();
                            mTile.tileId = cTile.ImgId;
                            mTile.tilesetKey = cTile.TilesetKey;
                            Point cellPosition = new Point(Canvas.GetLeft(this), Canvas.GetTop(this));//cTile.TransformToAncestor(grid).Transform(new Point(0, 0));
                            mTile.rectPos = new Int32Rect((int)cellPosition.X, (int)cellPosition.Y, (int)cTile.TileWidth, (int)cTile.TileHeight);
                            this.CollidedChanged += mTile.DragableLayout_CollidedChanged;
                            OnChildChanged(new DragableLayoutChildEventArgs(mTile));
                        }
                    }
                }
                container.ReleaseMouseCapture();
                Mouse.Capture(null);
            }
        }

        public void OnChildChanged(DragableLayoutChildEventArgs e)
        {
            ChildChanged?.Invoke(this, e);
        }
        public void OnCollidedChanged(DragableLayoutChildEventArgs e)
        {
            CollidedChanged?.Invoke(this, e);
        }

        private void container_PreviewMouseLeftButtonDown(object sender, MouseButtonEventArgs e)
        {
            if (ToolsEventHandle.DrawTool == ToolTypes.Block && ListChild.Count == 1)
            {
                Canvas panel = (Canvas)sender;
                Rectangle rec = new Rectangle()
                {
                    Width = this.Width,
                    Height = this.Height,
                    Stroke = Brushes.Green,
                    StrokeThickness = 1,
                };
                Canvas.SetTop(rec, 0);
                Canvas.SetLeft(rec, 0);
                panel.Children.Add(rec);

                OnCollidedChanged(new DragableLayoutChildEventArgs(true));
                return;
            }

            if (ToolsEventHandle.DrawTool ==  ToolTypes.Pen
                && ListChild.Count == 0
                && e.Handled == false)
            {

            }
        }

        private void container_MouseMove(object sender, MouseEventArgs e)
        {
            if (e.LeftButton == MouseButtonState.Pressed)
            {
                MessageBox.Show("Pressed!");
            }
        }
    }
}
