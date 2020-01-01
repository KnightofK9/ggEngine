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

        public int CourseId { get; set; }

        public int LecturerId { get; set; }

        #endregion
    }
}
