using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace WebApplication2.DTOs
{
    public class CourseStudentDTO
    {
        public int Id { get; set; }

        #region References

        public int CourseId { get; set; }

        public int StudentId { get; set; }

        #endregion
    }
}
