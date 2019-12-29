using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Threading.Tasks;

namespace WebApplication2.Models
{
    public class Message
    {
        [Key]
        public int Id { get; set; }

        [DisplayFormat(DataFormatString = "{0:yyyy/MM/dd HH:mm:ss}")]
        [DataType(DataType.DateTime)]
        public DateTime Time { get; set; }

        public string Content { get; set; }

        #region Relationships

        public ICollection<Report> Reports { get; set; }

        #endregion
    }
}
