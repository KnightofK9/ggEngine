using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace WebApplication2.DTOs
{
    public class AttendanceDTO
    {
        public int Id { get; set; }

        public int AttendanceStatus { get; set; }

        #region References

        public int StudentId { get; set; }

        #endregion
    }
}
