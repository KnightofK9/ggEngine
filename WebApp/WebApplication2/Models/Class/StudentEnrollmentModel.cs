using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace WebApplication2.Models
{
    public class StudentEnrollmentModel
    {
        public int Id { get; set; }
        public int ClassId { get; set; }
        public int StudentId { get; set; }
    }
}
