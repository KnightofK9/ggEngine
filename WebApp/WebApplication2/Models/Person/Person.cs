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
    [KnownType(typeof(Lecturer)), KnownType(typeof(Student))]
    public class Person
    {
        [Key]
        public int Id { get; set; }

        public string FirstName { get; set; }

        public string LastName { get; set; }

        public bool IsMale { get; set; }

        #region References

        public string UserId { get; set; }

        #endregion
    }
}
