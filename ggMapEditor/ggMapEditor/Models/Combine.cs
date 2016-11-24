using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ggMapEditor.Models
{
    public class Combine
    {
        private static int countId = 0;
        public string folderPath { get; set; }
        public string folderName { get; set; }
        public ObservableCollection<Models.TileMap> tileMaps { get; set; }
        public ObservableCollection<Models.Tileset> tilesets { get; set; }

        public Combine()
        {
            tilesets = new ObservableCollection<Tileset>();
            tileMaps = new ObservableCollection<TileMap>();
            folderName = "NewTileMap " + countId++;
        }
    }
}
