using System;
using System.Collections.Generic;
using System.Drawing;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Media;
using ggMapEditor.Views.Controls;
using Newtonsoft.Json;

namespace ggMapEditor.Models
{
    public class Tile
    {
        public long tileId;
        public string tilesetKey;   //Tên của tileset

        [JsonIgnore]
        public Int32Rect rectPos;
        [JsonIgnore]
        public bool isCollidedObject;

        public Tile()
        {
            isCollidedObject = false;
        }

        //public void DragableLayout_CollidedChanged(object sender, DragableLayoutChildEventArgs e)
        //{
        //    isCollidedObject = e.isCollidedObject;
        //}
    }
}