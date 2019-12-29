using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Threading.Tasks;
using WebApplication2.Data;

namespace WebApplication2.Models
{
    public class Rate
    {
        [Key]
        public int Id { get; set; }

        public Enums.RateLevel Level { get; set; }


        #region References

        public Student Student { get; set; }
        public Lession Lession { get; set; }

        #endregion
    }
}
