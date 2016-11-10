using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Threading;
using ggMapEditor.Helpers;

namespace ggMapEditor.ViewModels.Base
{
    public class BaseViewModel : INotifyPropertyChanged
    {
        private string statusMsg;
        public event EventHandle.MessageHandle StatusMsgChanged;

        protected virtual void SetStatusMsgChanged(MessageEventArgs e)
        {
            StatusMsgChanged?.Invoke(this, e);
        }

        public string StatusMsg
        {
            get { return statusMsg; }
            set
            {
                statusMsg = value;
                SetStatusMsgChanged(new MessageEventArgs(statusMsg));
            }
        }


        public event PropertyChangedEventHandler PropertyChanged;
        internal void RaisePropertyChanged(string property)
        {
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(property));
        }

        Nullable<bool> closeWindowFlag;
        public Nullable<bool> CloseWindowFlag
        {
            get { return closeWindowFlag; }
            set
            {
                closeWindowFlag = value;
                RaisePropertyChanged(nameof(CloseWindowFlag));
            }
        }
        private Nullable<bool> isSaveRecord;
        public virtual void CloseWindow(Nullable<bool> isSaveRecord = true)
        {
            this.isSaveRecord = isSaveRecord;
            Application.Current.Dispatcher.BeginInvoke(DispatcherPriority.Background, new Action(() =>
            {
                if (CloseWindowFlag == null)
                    CloseWindowFlag = true;
                else
                    CloseWindowFlag = !CloseWindowFlag;
            }));
            GC.Collect();
        }
        public virtual void OnWindowClosing(object sender, CancelEventArgs e)
        {
            if (isSaveRecord == true)
                return;
            CloseWindow();
        }
    }
}
