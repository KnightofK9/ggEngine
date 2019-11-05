using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Threading.Tasks;

namespace WebApplication2.Models
{
    public class LessionModel
    {
        public int Id { get; set; }
        public int ClassId { get; set; }
        [DisplayFormat(DataFormatString = "{0:dd MM yyyy}")]
        [DataType(DataType.Date)]
        public DateTime Time { get; set; }
        public int LecturerId { get; set; }
    }
}
