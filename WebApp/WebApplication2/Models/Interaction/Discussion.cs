using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Threading.Tasks;
using WebApplication2.Data;

namespace WebApplication2.Models
{
    public class Discussion
    {
        [Key]
        public int Id { get; set; }
        
        public Enums.DiscusstionStatus Status { get; set; }

        #region Relationships

        public ICollection<MessageLecturer> MessageLecturers { get; set; }
        public ICollection<MessageStudent> StudentMessages { get; set; }

        #endregion

        #region References

        public Lession Lession { get; set; }

        #endregion
    }
}
