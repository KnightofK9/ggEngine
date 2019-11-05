using Microsoft.EntityFrameworkCore;
using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Threading.Tasks;

namespace WebApplication2.Models
{
    public class StudentModel : PersonModel
    {
        public string StudentCode { get; set; }

        public string NickName { get; set; }
    }
}
