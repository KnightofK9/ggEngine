using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Threading.Tasks;

namespace WebApplication2.Models
{
    public class SubmissionModel
    {
        [Key]
        public int Id { get; set; }

        public DateTime Time { get; set; }

        public int? Point { get; set; }

        // Aggregation

        public StudentModel Student { get; set; }
        
        // Composition

        public ICollection<AnswerModel> Answers { get; set; }
    }
}
