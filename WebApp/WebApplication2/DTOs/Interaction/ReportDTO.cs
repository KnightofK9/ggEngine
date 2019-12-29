using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using WebApplication2.Models;

namespace WebApplication2.DTOs
{
    public class ReportDTO
    {
        public int Id { get; set; }

        public string Comment { get; set; }

        #region References

        public int StudentId { get; set; }

        #endregion
    }    
}
