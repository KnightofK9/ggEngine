using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ggMapEditor.Helpers
{
    public class EventHandle
    {
        public delegate void MessageHandle(object sender, MessageEventArgs e);
    }

    public class MessageEventArgs
    {
        public readonly string statusMsg;
        public MessageEventArgs(string msg)
        {
            statusMsg = msg;
        }
    }
}
