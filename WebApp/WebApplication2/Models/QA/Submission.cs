using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Threading.Tasks;

namespace WebApplication2.Models
{
    public class Submission
    {
        [Key]
        public int Id { get; set; }

        [DisplayFormat(DataFormatString = "{0:yyyy/MM/dd HH:mm:ss}")]
        [DataType(DataType.DateTime)]
        public DateTime Time { get; set; }

        public int? Point { get; set; }

        #region Relationships

        public ICollection<Answer> Answers { get; set; }

        #endregion

        #region References

        public Test Test { get; set; }
        public Student Student { get; set; }

        #endregion

    }
}
