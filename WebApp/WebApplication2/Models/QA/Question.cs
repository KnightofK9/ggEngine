using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Threading.Tasks;

namespace WebApplication2.Models
{
    public class Question
    {
        [Key]
        public int Id { get; set; }

        public string Content { get; set; }

        public int Solution { get; set; }

        #region Relationships

        public ICollection<Option> Options { get; set; }

        #endregion

        #region Reference

        public int TestId { get; set; }

        #endregion
    }
}
