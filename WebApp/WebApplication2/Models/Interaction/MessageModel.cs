using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Threading.Tasks;

namespace WebApplication2.Models
{
    public class MessageModel
    {
        [Key]
        public int Id { get; set; }

        public DateTime Time { get; set; }

        public string Content { get; set; }
        
        // Composition

        public ICollection<ReportModel> Reports { get; set; }
    }
}
