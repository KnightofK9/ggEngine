using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Newtonsoft.Json;

namespace ggMapEditor.Models
{
    public class TileMap
    {
        public int width;     //actual width
        public int height;    //actual height
        public int leafWidth;
        public int leafHeight;
        public int totalLeafNodeSize;
        public int totalNodeSize;
        //public int tileSize;
        public ObservableCollection<QuadTree.QuadNode> quadNodeList;

        [JsonIgnore]
        public int row;
        [JsonIgnore]
        public int column;
        [JsonIgnore]
        public int mapWidth;    //user choosed
        [JsonIgnore]
        public int mapHeight;   //user choosed
        [JsonIgnore]
        public ObservableCollection<Models.Tile> listTile;
        //public ObservableCollection<Models.Layer> layers { get; set; }  

        public TileMap()
        {
            listTile = new ObservableCollection<Tile>();
            quadNodeList = new ObservableCollection<QuadTree.QuadNode>();
            leafWidth = leafHeight = 32;
            //tileSize = 32;
            //tilesets = new ObservableCollection<Tileset>();
            //layers = new ObservableCollection<Layer>();
        }
    }
}
