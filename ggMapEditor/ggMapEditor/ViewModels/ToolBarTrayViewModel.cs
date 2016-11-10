using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using ggMapEditor.Commands;

namespace ggMapEditor.ViewModels
{
    class ToolBarTrayViewModel: Base.BaseViewModel
    {
        #region Private Members

        #endregion


        #region Properties
        #endregion

        #region Commands
        public RelayCommand  AddCommand { get; set; }
        #endregion

        #region Constructors
        public ToolBarTrayViewModel()
        {

        }
        #endregion
    }
}
