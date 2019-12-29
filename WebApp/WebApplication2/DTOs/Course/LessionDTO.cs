using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Threading.Tasks;

namespace WebApplication2.DTOs
{
    public class LessionDTO
    {
        public int Id { get; set; }

        public string Time { get; set; }

        #region References

        public int LecturerId { get; set; }
        public int CourseId { get; set; }

        #endregion
    }
}
