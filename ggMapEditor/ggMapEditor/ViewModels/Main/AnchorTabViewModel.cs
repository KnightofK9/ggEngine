using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using ggMapEditor.Commands;

namespace ggMapEditor.ViewModels.Main
{
    class AnchorTabViewModel : Base.BaseViewModel
    {
        #region Properties
        //private bool isClosed;
        //public bool IsClosed
        //{
        //    get { return isClosed; }
        //    set
        //    {
        //        isClosed = value;
        //        RaisePropertyChanged(nameof(IsClosed));
        //    }
        //}

        private bool canClose;
        public bool CanClose
        {
            get { return canClose; }
            set
            {
                canClose = value;
                RaisePropertyChanged(nameof(CanClose));
            }
        }

        private string title;
        public string Title
        {
            get { return title; }
            set
            {
                title = value;
                RaisePropertyChanged(nameof(Title));
            }
        }
        #endregion

        #region Commands
        public RelayCommand CloseCommand { get; set; }
        #endregion

        public AnchorTabViewModel()
        {
            this.CanClose = true;
            //this.IsClosed = false;
            CloseCommand = new RelayCommand(Close);
        }

        public void Close(object paramter)
        {
            //MessageBox.Show("Closing dock window...");
            //this.IsClosed = true;
        }
    }
}
