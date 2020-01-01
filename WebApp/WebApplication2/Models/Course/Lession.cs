using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Threading.Tasks;

namespace WebApplication2.Models
{
    public class Lession
    {
        [Key]
        public int Id { get; set; }

        [DisplayFormat(DataFormatString = "{0:yyyy/MM/dd}")]
        [DataType(DataType.Date)]
        public DateTime Time { get; set; }

        #region Relationships

        public ICollection<Discussion> Discussions { get; set; }
        public ICollection<Rate> Rates { get; set; }
        public ICollection<Document> Documents { get; set; }
        public ICollection<Attendance> Attendances { get; set; }
        public ICollection<Test> Tests { get; set; }

        #endregion

        #region References

        public int LecturerId { get; set; }
        public int CourseId { get; set; }

        #endregion
    }
}