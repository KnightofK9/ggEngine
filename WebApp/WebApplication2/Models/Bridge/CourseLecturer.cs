using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Threading.Tasks;
using WebApplication2.Data;

namespace WebApplication2.Models
{
    public class CourseLecturer
    {
        [Key]
        public int Id { get; set; }

        public Enums.TeachingType Type { get; set; }

        #region References

        public Course Course { get; set; }

        public Lecturer Lecturer { get; set; }

        #endregion
    }
}
