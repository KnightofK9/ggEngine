using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace WebApplication2.DTO
{
    public class OptionDTO
    {
        public int Id { get; set; }

        public string Content { get; set; }

        #region References

        public int QuestionDTO { get; set; }

        #endregion
    }
}
