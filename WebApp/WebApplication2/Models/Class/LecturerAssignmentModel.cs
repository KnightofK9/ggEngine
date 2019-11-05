using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace WebApplication2.Models
{
    public class LecturerAssignmentModel
    {
        public int Id { get; set; }
        public int ClassId { get; set; }
        public int MajorLecturerId { get; set; }
        public int MinorLecturerId { get; set; }
    }
}
