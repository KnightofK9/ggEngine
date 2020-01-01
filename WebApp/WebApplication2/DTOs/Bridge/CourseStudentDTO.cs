using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using WebApplication2.Data;
using WebApplication2.Models;

namespace WebApplication2.DTOs
{
    public class CourseStudentDTO
    {
        public int Id { get; set; }

        #region References

        public int CourseId { get; set; }

        public int StudentId { get; set; }

        #endregion

        public static CourseStudent ToModel(CourseStudentDTO courseStudentDTO, ApplicationDbContext context)
        {
            return new CourseStudent
            {
                Id = courseStudentDTO.Id,
                
                CourseId = courseStudentDTO.CourseId,
                StudentId = courseStudentDTO.StudentId
            };
        }

        public static CourseStudentDTO ToDTO(CourseStudent courseStudent)
        {
            return new CourseStudentDTO
            {
                Id = courseStudent.Id,
                CourseId = courseStudent.CourseId,
                StudentId = courseStudent.StudentId
            };
        }
    }
}
