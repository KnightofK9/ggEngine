using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Threading.Tasks;

namespace WebApplication2.Models
{
    public class Semester
    {
        [Key]
        public int Id { get; set; }

        public string Name { get; set; }

        #region Relationships

        public ICollection<Course> Courses { get; set; }

        #endregion
    }
}
