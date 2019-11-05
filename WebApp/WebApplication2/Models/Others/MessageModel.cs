using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace WebApplication2.Models
{
    public class MessageModel
    {
        public int Id { get; set; }
        public int DiscussionId { get; set; }
        public int PersonId { get; set; }
        public bool Anonymous { get; set; }
        public DateTime Time { get; set; }
        public string Content { get; set; }
    }
}
