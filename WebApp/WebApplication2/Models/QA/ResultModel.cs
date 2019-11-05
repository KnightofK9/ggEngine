using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Threading.Tasks;

namespace WebApplication2.Models
{
    public class ResultModel
    {
        public int Id { get; set; }
        public int SubmissionId { get; set; }
        public int Point { get; set; }
    }
}
