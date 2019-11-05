using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using WebApplication2.Data;

namespace WebApplication2.Models
{
    public class RateModel
    {
        public int Id { get; set; }
        public int LessionId { get; set; }
        public int StudentId { get; set; }
        public Enums.Rate Rate { get; set; }
        public string Comment { get; set; }
        public bool Anonymous { get; set; }
    }
}
