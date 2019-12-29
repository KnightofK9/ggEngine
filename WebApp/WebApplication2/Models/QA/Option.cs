using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Threading.Tasks;

namespace WebApplication2.Models
{
    public class Option
    {
        [Key]
        public int Id { get; set; }

        public string Content { get; set; }

        #region References

        public Question Question { get; set; }

        #endregion
    }
}
