using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace WebApplication2.DTO
{
    public class PersonDTO
    {
        public int Id { get; set; }

        public string FirstName { get; set; }

        public string LastName { get; set; }

        public bool IsMale { get; set; }

        #region References

        public int UserId { get; set; }

        #endregion
    }
}
