using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Threading.Tasks;
using WebApplication2.Data;

namespace WebApplication2.Models
{
    public class TestModel
    {
        [Key]
        public int Id { get; set; }

        public string Title { get; set; }

        public DateTime Deadline { get; set; }

        public Enums.DiscusstionStatus Status { get; set; }
        
        // Composition

        public ICollection<QuestionModel> Questions { get; set; }
        public ICollection<SubmissionModel> Submissions { get; set; }
    }
}
