using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace WebApplication2.DTO
{
    public class LecturerDTO : PersonDTO
    {
        public string Code { get; set; }

        public int AcademicRank { get; set; }
    }
}
