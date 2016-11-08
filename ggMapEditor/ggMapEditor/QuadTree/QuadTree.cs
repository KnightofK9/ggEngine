using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using ggMapEditor.QuadTree;

namespace ggMapEditor.QuadTree
{
    public class QuadTree<T>
    {
        public static int MaxObjPerCell = 1; // so phan tu toi da trong mot o
        public static int MinCellWidth = 32;
        public static int MinCellHeight = 32;

        private ObservableCollection<QTObject> listObj;
        private QuadNode root;

        public QuadTree(Int32Rect rect, ObservableCollection<QTObject> objs)
        {
            listObj = objs;
            root = new QuadNode(rect, null);
        }

        public void Clear()
        {
            root.Clear();
        }

        public void CreateQuadTree()
        {
            foreach (var o in listObj)
                root.Insert(o);
        }

        public ObservableCollection<QuadNode> RetrieveQuadNodes()
        {
            var listNode = root.RetrieveQuadNodes();
            //listNode.Sort(delegate (QuadNode n1, QuadNode n2) { return n1.id.CompareTo(n2.id); });
            //listNode.Sort((a, b) => a.id.CompareTo(b.id));
            listNode = new ObservableCollection<QuadNode>(listNode.OrderBy(n => n.id));
            return listNode;
        }

        public int GetTotalNodeSize()
        {
            return root.GetTotalNodeSize();
        }
        public int GetTotalLeafNodeSize()
        {
            return root.GetTotalLeafNodeSize();
        }
    }
}
