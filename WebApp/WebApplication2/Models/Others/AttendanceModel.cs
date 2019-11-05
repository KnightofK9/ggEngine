using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using WebApplication2.Data;

namespace WebApplication2.Models
{
    public class AttendanceModel
    {
        public int Id { get; set; }
        public int LessionId { get; set; }
        public int StudentId { get; set; }
        public Enums.AttendanceStatus AttendanceStatus { get; set; }
    }
}
