using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Threading.Tasks;

namespace WebApplication2.Models
{
    public class Report
    {
        [Key]
        public int Id { get; set; }

        public string Comment { get; set; }

        #region References

        public Student Student { get; set; }

        #endregion
    }
}
