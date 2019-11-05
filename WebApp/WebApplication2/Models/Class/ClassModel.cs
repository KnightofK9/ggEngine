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
        public int Id { get; set; }
        public string ClassCode { get; set; }
        public string Name { get; set; }

        [ForeignKey("SemesterModel")]
        public int SemesterId { get; set; }
        [DisplayFormat(DataFormatString = "{0:dd MM yyyy}")]
        [DataType(DataType.Date)]
        public DateTime StartDate { get; set; }
        [DisplayFormat(DataFormatString = "{0:dd MM yyyy}")]
        [DataType(DataType.Date)]
        public DateTime EndDate { get; set; }
    }
}
