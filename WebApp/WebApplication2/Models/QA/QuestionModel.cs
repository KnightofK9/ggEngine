using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Threading.Tasks;

namespace WebApplication2.Models
{
    public class QuestionModel
    {
        [Key]
        public int Id { get; set; }

        public string Content { get; set; }

        public int Solution { get; set; }

        // Composition

        public ICollection<OptionModel> Options { get; set; }
    }
}
