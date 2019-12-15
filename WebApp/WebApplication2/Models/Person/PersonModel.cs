using Microsoft.AspNetCore.Identity;
using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;
using System.Linq;
using System.Runtime.Serialization;
using System.Threading.Tasks;

namespace WebApplication2.Models
{
    [KnownType(typeof(LecturerModel)), KnownType(typeof(StudentModel))]
    public class PersonModel
    {
        [Key]
        public int Id { get; set; }

        public string FirstName { get; set; }

        public string LastName { get; set; }

        public string FullName { get { return FirstName + ' ' + LastName; } }

        public bool IsMale { get; set; }

        // Composition

        public UserModel User { get; set; }
    }
}
