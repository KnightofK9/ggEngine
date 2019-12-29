using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Threading.Tasks;
using WebApplication2.Data;

namespace WebApplication2.Models
{
    public class Lecturer : Person
    {
        public string Code { get; set; }

        public Enums.AcademicRank AcademicRank { get; set; }

        #region Relationships

        public ICollection<CourseLecturer> CourseLecturers { get; set; }
        public ICollection<Lession> Lessions { get; set; }
        public ICollection<MessageLecturer> MessageLecturers { get; set; }

        #endregion
    }
}
