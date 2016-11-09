using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using ggMapEditor.Helpers;
using Newtonsoft.Json;

namespace ggMapEditor.QuadTree
{
    public struct QTObject
    {
        public int type;
        public Models.Tile value;
    }

    public class QuadNode
    { 
        public int x;
        public int y;
        public int width;
        public int height;

        public long leftTop { get; set; }
        public long rightTop { get; set; }
        public long rightBottom { get; set; }
        public long leftBottom { get; set; }

        public long id;
        public ObservableCollection<QTObject> tileList = new ObservableCollection<QTObject>();

        private Dictionary<long, QuadNode> listChild;




        public QuadNode(Int32Rect rect, ObservableCollection<QTObject> tiles, long id = -1)
        {
            this.id = id;
            listChild = null;

            if (tiles != null)
                tileList = tiles;

            x = rect.X;
            y = rect.Y;
            width = rect.Width;
            height = rect.Height;
        }


        public void Clear()
        {
            if (listChild != null)
            {
                listChild[leftTop].Clear();
                listChild[rightTop].Clear();
                listChild[rightBottom].Clear();
                listChild[leftBottom].Clear();
                tileList.Clear();
            }
        }

        private bool IsContain(QTObject obj)
        {
            var rect = obj.value.rectPos;
            return !(rect.X + rect.Width <= x
                    || rect.Y + rect.Height <= y
                    || rect.X >= x + width
                    || rect.Y >= y + height);
        }

        public void Insert(QTObject obj)
        {
            Debug.Print("Node: " + id + "objs id: " + obj.value.tileId +", objs count: " + tileList.Count);
            if (listChild != null)
            {
                if (listChild[leftTop].IsContain(obj))
                    listChild[leftTop].Insert(obj);
                if (listChild[rightTop].IsContain(obj))
                    listChild[rightTop].Insert(obj);
                if (listChild[rightBottom].IsContain(obj))
                    listChild[rightBottom].Insert(obj);
                if (listChild[leftBottom].IsContain(obj))
                    listChild[leftBottom].Insert(obj);
            }
            else
            {
                if (this.IsContain(obj))
                    tileList.Add(obj);
                if (tileList.Count > QuadTree<Models.Tile>.MaxObjPerCell
                    && height > QuadTree<Models.Tile>.MinCellHeight
                    && width > QuadTree<Models.Tile>.MinCellWidth)
                {
                    Split();
                    Debug.Print("Split "
                        + leftTop.ToString() + ", "
                        + rightTop.ToString() + ", "
                        + rightBottom.ToString() + ", "
                        + leftBottom.ToString());

                    while (tileList.Count > 0)
                    {
                        var lastTile = tileList.Last();
                        tileList.Remove(tileList.Last());

                        if (listChild[leftTop].IsContain(lastTile))
                        {
                            listChild[leftTop].Insert(lastTile);
                        }
                        if (listChild[rightTop].IsContain(lastTile))
                        {
                            listChild[rightTop].Insert(lastTile);
                        }
                        if (listChild[rightBottom].IsContain(lastTile))
                        {
                            listChild[rightBottom].Insert(lastTile);
                        }
                        if (listChild[leftBottom].IsContain(lastTile))
                        {
                            listChild[leftBottom].Insert(lastTile);

                        }
                    }
                }
            }
        }

        private void Split()
        {
            leftTop = ((id + 1) * 4);
            rightTop = ((id + 1) * 4) + 1;
            rightBottom = ((id + 1) * 4) + 2;
            leftBottom = ((id + 1) * 4) + 3;

            listChild = new Dictionary<long, QuadNode>();
            listChild.Add(leftTop, new QuadNode     (new Int32Rect(x,              y,              width / 2, height / 2), null, leftTop));
            listChild.Add(rightTop, new QuadNode    (new Int32Rect(x + width / 2,  y,              width / 2, height / 2), null, rightTop));
            listChild.Add(rightBottom, new QuadNode (new Int32Rect(x + width / 2,  y + height / 2, width / 2, height / 2), null, rightBottom));
            listChild.Add(leftBottom, new QuadNode  (new Int32Rect(x,              y + height / 2, width / 2, height / 2), null, leftBottom));
            //hasChild = true;
        }

        public ObservableCollection<QuadNode> RetrieveQuadNodes()
        {
            ObservableCollection<QuadNode> listNode = new ObservableCollection<QuadNode>();
            listNode.Add(this);
            if (listChild != null)
            {
                listNode = listNode.Union(listChild[leftTop].RetrieveQuadNodes()).ToObservableCollection();
                listNode = listNode.Union(listChild[rightTop].RetrieveQuadNodes()).ToObservableCollection();
                listNode = listNode.Union(listChild[rightBottom].RetrieveQuadNodes()).ToObservableCollection();
                listNode = listNode.Union(listChild[leftBottom].RetrieveQuadNodes()).ToObservableCollection();
            }
            return listNode;
        }

        public bool ShouldSerializeChildId()
        {
            return !(listChild[leftTop] == null
                    || listChild[rightTop] == null
                    || listChild[rightBottom] == null
                    || listChild[leftBottom] == null);
        }
        public bool ShouldSerializeleftTop()
        {
            return !(listChild == null || listChild[leftTop] == null);
        }
        public bool ShouldSerializerightTop()
        {
            return !(listChild == null || listChild[rightTop] == null);
        }
        public bool ShouldSerializerightBottom()
        {
            return !(listChild == null || listChild[rightBottom] == null);
        }
        public bool ShouldSerializeleftBottom()
        {
            return !(listChild == null || listChild[leftBottom] == null);
        }

        public int GetTotalNodeSize()
        {
            if (listChild == null)
                return 1;
            int node = 1;
            node += listChild[leftTop].GetTotalNodeSize();
            node += listChild[rightTop].GetTotalNodeSize();
            node += listChild[rightBottom].GetTotalNodeSize();
            node += listChild[leftBottom].GetTotalNodeSize();

            return node;
        }
        public int GetTotalLeafNodeSize()
        {
            if (listChild == null)
                return 1;
            int node = 0;
            node += listChild[leftTop].GetTotalNodeSize();
            node += listChild[rightTop].GetTotalNodeSize();
            node += listChild[rightBottom].GetTotalNodeSize();
            node += listChild[leftBottom].GetTotalNodeSize();

            return node;

        }

        //public ObservableCollection<QTObject<T>> RetrieveObject()
        //{
        //    ObservableCollection<QTObject<T>> listReturn = listObj;
        //    if (hasChild)
        //    {
        //            listReturn = JoinList(listReturn, topLeft.RetrieveObject());
        //            listReturn = JoinList(listReturn, topRight.RetrieveObject());
        //            listReturn = JoinList(listReturn, bottomLeft.RetrieveObject());
        //            listReturn = JoinList(listReturn, bottomRight.RetrieveObject());
        //    }
        //    return listReturn;
        //}
        //private ObservableCollection<QTObject<T>> JoinList(ObservableCollection<QTObject<T>> list1, ObservableCollection<QTObject<T>> list2)
        //{
        //    ObservableCollection<QTObject<T>> result = list1;
        //    foreach (var item in list2)
        //        result.Add(item);

        //    return result;
        //}
    }
}
