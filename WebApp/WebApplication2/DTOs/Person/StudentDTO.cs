using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace WebApplication2.DTOs
{
    public class StudentDTO : PersonDTO
    {
        public string Code { get; set; }

        public string NickName { get; set; }

        public bool Anonymous { get; set; }        
    }
}
