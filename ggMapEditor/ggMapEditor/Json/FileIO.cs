using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using ggMapEditor.QuadTree;
using Newtonsoft.Json;

namespace ggMapEditor.Json
{
    public static class ConvertJson
    {
        public static string SaveFile(Models.Combine combine, int currentTab)
        {
            // Dua vao QuadTree de lay id, rect
            Models.TileMap tileMap = combine.tileMaps[0];
            ObservableCollection<QTObject> listQTObj = new ObservableCollection<QTObject>();
            foreach (var tile in tileMap.listTile)
            {
                QTObject obj = new QTObject();
                obj.value = tile;
                obj.isCollidedObject = tile.isCollidedObject;
                listQTObj.Add(obj);
            }
            Int32Rect rect = new Int32Rect(0, 0, tileMap.width, tileMap.height);
            QuadTree<Models.Tile> quadTree = new QuadTree<Models.Tile>(rect, listQTObj);
            quadTree.CreateQuadTree();

            tileMap.quadNodeList = quadTree.RetrieveQuadNodes();
            tileMap.totalNodeSize = quadTree.GetTotalNodeSize();
            tileMap.totalLeafNodeSize = quadTree.GetTotalLeafNodeSize();

            string json = JsonConvert.SerializeObject(tileMap);
            string filePath = combine.folderPath + "\\" + combine.folderName + ".json";

            

            if (!Directory.Exists(filePath))
                Directory.CreateDirectory(combine.folderPath);
            System.IO.File.WriteAllText(filePath, json);
            return json;
        }
    }
}
