using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using WebApplication2.Data;

namespace WebApplication2.Models
{
    public class DiscussionModel
    {
        public int Id { get; set; }
        public int LessionId { get; set; }
        public Enums.DiscusstionStatus Status { get; set; }
    }
}
