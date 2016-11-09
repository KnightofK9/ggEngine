using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Controls;
using System.Windows.Input;

namespace ggMapEditor.Helpers
{
    public static class ToolsEventHandle
    {
        //Tool: các công cụ vẽ, xóa, tạo block, di chuyển qua lại (colision)
        //Tạo event bắt sự kiện chuyển loại công cụ
        public delegate void ToolChangeHandle(object sender, ToolTypeEventArgs e);
        public static event ToolChangeHandle ToolChanged;
        private static ToolTypes toolType;

        public static ToolTypes DrawTool
        {
            get { return toolType; }
            set
            {
                toolType = value;
                OnChildChanged(new ToolTypeEventArgs(toolType));
            }
        }

        public class ToolTypeEventArgs
        {
            public readonly ToolTypes toolTypes;
            public ToolTypeEventArgs(ToolTypes type)
            {
                this.toolTypes = type;
            }
        }

        private static void OnChildChanged(ToolTypeEventArgs e)
        {
            ToolChanged?.Invoke(toolType, e);
        }

        public static void SetMouseCusor(object sender, ToolTypeEventArgs e)
        {
            Mouse.SetCursor(Cursors.Cross);
        }
    }
}
