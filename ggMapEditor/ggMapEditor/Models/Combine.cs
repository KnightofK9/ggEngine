using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ggMapEditor.Models
{
    public class Combine
    {
        public string folderPath { get; set; }
        public string folderName { get; set; }
        public Models.TileMap tileMap { get; set; }
        public Models.Tileset tileset { get; set; }

        public Combine()
        {
            //tileMap = new TileMap();
            //tileset = new Tileset();
            tileMap = null;
            tileset = null;
            folderName = "NewTileMap";
        }
    }
}
