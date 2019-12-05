using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Threading.Tasks;

namespace WebApplication2.Models
{
    public class LessionModel
    {
        [Key]
        public int Id { get; set; }

        [DisplayFormat(DataFormatString = "{0:dd MM yyyy}")]
        [DataType(DataType.Date)]
        public DateTime Time { get; set; }

        // Aggregation

        public LecturerModel Lecturer { get; set; }

        // Composition

        public ICollection<DiscussionModel> Discussions { get; set; }        
        public ICollection<RateModel> Rates { get; set; }
        public ICollection<DocumentModel> Documents { get; set; }
        public ICollection<AttendanceModel> Attendances { get; set; }
        public ICollection<TestModel> Tests { get; set; }
    }
}