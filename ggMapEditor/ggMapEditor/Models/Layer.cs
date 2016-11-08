using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ggMapEditor.Models
{

    public class Layer : INotifyPropertyChanged
    {
        private static int id;
        public static int Id
        {
            get { return id; }
            private set { id = value; }
        }
        private string name;
        public string Name
        {
            get { return name; }
            set
            {
                name = value;
                RaisePropertyChanged("Name");
            }
        }
        private bool visible = true;
        public bool Visible
        {
            get { return visible; }
            set
            {
                visible = value;
                RaisePropertyChanged("Visible");
            }
        }
        private ObservableCollection<Views.Controls.Tile> tiles;
        public ObservableCollection<Views.Controls.Tile> Tiles
        {
            get { return tiles; }
            set
            {
                Tiles = tiles;
                RaisePropertyChanged("Tiles");
            }
        }

        public Layer()
        {
            Id++;
            Name = "Layer " + Id.ToString();
            tiles = new ObservableCollection<Views.Controls.Tile>();
        }

        public event PropertyChangedEventHandler PropertyChanged;
        internal void RaisePropertyChanged(string property)
        {
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(property));
        }
    }
}
