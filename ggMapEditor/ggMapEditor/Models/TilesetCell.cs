using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ggMapEditor.Models
{
    public class TilesetCell
    {
        private static long countId = 0;
        public long id;
        public int x;
        public int y;

        public TilesetCell()
        {
            id = TilesetCell.countId++;
        }

    }
}
