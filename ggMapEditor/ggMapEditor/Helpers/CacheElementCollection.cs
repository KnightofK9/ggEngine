using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;

namespace ggMapEditor.Helpers
{
    public static class CacheElementCollection
    {
        private static Dictionary<Point, Views.Controls.Tile> cTiles;
        //public static ObservableCollection<Views.Controls.Tile> Elements { get; set; }
        public static Dictionary<Point, UIElement> Elements { get; set; }




        public static Dictionary<Point, UIElement> TranslatePositionCollection
            (this Dictionary<Point, UIElement> elements, Point des, Point desInLayout)
        {
            if (elements == null || elements.Count == 0)
                return null;

            //lấy position tương đối
            var left = elements.Keys.Min(p => p.X);
            var right = elements.Keys.Max(p => p.X);
            var top = elements.Keys.Min(p => p.Y);
            var bottom = elements.Keys.Max(p => p.Y);

            Point centroit = new Point((right + left) / 2, (bottom + top) / 2);

            // chuyển tọa độ
            // centroit - des : to get distance
            // 
            //var X = centroit.X - 2*des.X + desInLayout.X ;
            //var Y = centroit.Y - 2*des.Y + desInLayout.Y;

            var temp = new Dictionary<Point, UIElement>();
            foreach (var e in elements)
                temp.Add(new Point(desInLayout.X + (e.Key.X - centroit.X), desInLayout.Y + (e.Key.Y - centroit.Y)), e.Value);

            return temp;
        }
    }
}
