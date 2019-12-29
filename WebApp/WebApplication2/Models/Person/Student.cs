using Microsoft.EntityFrameworkCore;
using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Threading.Tasks;

namespace WebApplication2.Models
{
    public class Student : Person
    {
        public string Code { get; set; }

        public string NickName { get; set; }

        public bool Anonymous { get; set; }

        #region Relationships

        public ICollection<CourseStudent> CourseStudents { get; set; }
        public ICollection<Attendance> Attendances { get; set; }
        public ICollection<MessageStudent> MessageStudents { get; set; }
        public ICollection<Rate> Rates { get; set; }
        public ICollection<Report> Reports { get; set; }
        public ICollection<Submission> Submissions { get; set; }


        #endregion
    }
}
