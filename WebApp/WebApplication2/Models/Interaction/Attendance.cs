using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Threading.Tasks;
using WebApplication2.Data;

namespace WebApplication2.Models
{
    public class Attendance
    {
        [Key]
        public int Id { get; set; }

        public Enums.AttendanceStatus AttendanceStatus { get; set; }

        #region References

        public Student Student { get; set; }

        #endregion
    }
}
