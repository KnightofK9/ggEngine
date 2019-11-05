using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace WebApplication2.Models
{
    public class ReportModel
    {
        public int Id { get; set; }
        public int MessageId { get; set; }
        public int ReportPersonId { get; set; }
        public string Comment { get; set; }
    }
}
