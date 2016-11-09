using System;
using System.Collections.Generic;
using System.Drawing;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Media;
using Newtonsoft.Json;

namespace ggMapEditor.Models
{
    public class Tile
    {
        public long tileId;
        public string tilesetKey;   //Tên của tileset

        [JsonIgnore]
        public Int32Rect rectPos;

        public Tile()
        {
        }
    }
}