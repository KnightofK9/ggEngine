using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Threading.Tasks;
using WebApplication2.Data;

namespace WebApplication2.Models
{
    public class Test
    {
        [Key]
        public int Id { get; set; }

        public string Title { get; set; }

        [DisplayFormat(DataFormatString = "{0:yyyy/MM/dd HH:mm:ss}")]
        [DataType(DataType.DateTime)]
        public DateTime Deadline { get; set; }

        public Enums.DiscusstionStatus Status { get; set; }

        #region Relationship

        public ICollection<Question> Questions { get; set; }
        public ICollection<Submission> Submissions { get; set; }

        #endregion

        #region References

        public int LessionId { get; set; }
        
        #endregion
    }
}
