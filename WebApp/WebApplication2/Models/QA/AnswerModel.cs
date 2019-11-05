using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace WebApplication2.Models
{
    public class AnswerModel
    {
        public int Id { get; set; }
        public int SubmissionId { get; set; }
        public int QuestionId { get; set; }
        public string Content { get; set; }
    }
}
