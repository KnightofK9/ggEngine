using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Threading.Tasks;
using WebApplication2.Data;

namespace WebApplication2.Models
{
    public class DiscussionModel
    {
        [Key]
        public int Id { get; set; }
        
        public Enums.DiscusstionStatus Status { get; set; }

        // Composition

        public ICollection<LecturerMessageModel> LecturerMessages { get; set; }
        public ICollection<StudentMessageModel> StudentMessages { get; set; }
    }
}
