using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Threading.Tasks;

namespace WebApplication2.DTO
{
    public class CourseDTO
    {
        public int Id { get; set; }

        public string Code { get; set; }

        public string Name { get; set; }

        public string StartDate { get; set; }

        public string EndDate { get; set; }

        public int StudentNumber { get; }

        #region References

        public int SemesterId { get; set; }

        #endregion
    }
}
