using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;
using System.Linq;
using System.Threading.Tasks;

namespace WebApplication2.Models
{
    public class ClassModel
    {
        [Key]
        public int Id { get; set; }

        public string ClassCode { get; set; }
        
        public string Name { get; set; }
  
        [DisplayFormat(DataFormatString = "{0:dd MM yyyy}")]
        [DataType(DataType.Date)]
        public DateTime StartDate { get; set; }

        [DisplayFormat(DataFormatString = "{0:dd MM yyyy}")]
        [DataType(DataType.Date)]
        public DateTime EndDate { get; set; }

        public int StudentNumberLimit { get; set; }

        // Aggregation

        public SemesterModel Semester { get; set; }
        public ICollection<LecturerModel> TheoreticalLecturers { get; set; }
        public ICollection<LecturerModel> PracticalLecturers { get; set; }

        // Composition

        public ICollection<LessionModel> Lessions { get; set; }     
    }
}
