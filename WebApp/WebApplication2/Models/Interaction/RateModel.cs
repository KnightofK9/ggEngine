using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Threading.Tasks;
using WebApplication2.Data;

namespace WebApplication2.Models
{
    public class RateModel
    {
        [Key]
        public int Id { get; set; }

        public Enums.Rate Rate { get; set; }

        // Aggregation

        public StudentModel Student { get; set; }
    }
}
