using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace WebApplication2.DTOs
{
    public class CourseLecturerDTO
    {
        public int Id { get; set; }

        public int Type { get; set; }

        #region References

        public int CourseId { get; set; }

        public int LecturerId { get; set; }

        #endregion
    }
}
