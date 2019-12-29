using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace WebApplication2.DTOs
{
    public class RateDTO
    {
        public int Id { get; set; }

        public int Level { get; set; }


        #region References

        public int StudentId { get; set; }
        public int LessionId { get; set; }

        #endregion
    }
}
