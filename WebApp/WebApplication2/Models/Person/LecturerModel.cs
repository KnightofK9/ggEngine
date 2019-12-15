using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Threading.Tasks;
using WebApplication2.Data;

namespace WebApplication2.Models
{
    public class LecturerModel : PersonModel
    {
        public string LecturerCode { get; set; }

        public Enums.AcademicRank AcademicRank { get; set; }
    }
}
