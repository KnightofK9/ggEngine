using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace WebApplication2.DTOs
{
    public class QuestionDTO
    {
        public int Id { get; set; }

        public string Content { get; set; }

        public int Solution { get; set; }

        #region Reference

        public int TestId { get; set; }

        #endregion
    }
}
