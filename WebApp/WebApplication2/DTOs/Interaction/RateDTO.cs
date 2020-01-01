using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using WebApplication2.Data;
using WebApplication2.Models;

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

        public static Rate ToModel(RateDTO rateDTO, ApplicationDbContext context)
        {
            return new Rate
            {
                Id = rateDTO.Id,
                Level = (Enums.RateLevel)rateDTO.Level,
                
                StudentId = rateDTO.StudentId,
                LessionId = rateDTO.LessionId
            };
        }

        public static RateDTO ToDTO(Rate rate)
        {
            return new RateDTO
            {
                Id = rate.Id,
                Level = (int)rate.Level,
                
                StudentId = rate.StudentId,
                LessionId = rate.LessionId                 
            };
        }
    }
}
