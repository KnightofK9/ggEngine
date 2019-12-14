using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Threading.Tasks;

namespace WebApplication2.Models
{
    public class ReportModel
    {
        [Key]
        public int Id { get; set; }

        public string Comment { get; set; }

        // Aggregation

        public StudentModel ReportPerson { get; set; }
    }
}
