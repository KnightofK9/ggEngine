using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using WebApplication2.Data;
using WebApplication2.Models;

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

        public static CourseLecturer ToModel(CourseLecturerDTO courseLecturerDTO, ApplicationDbContext context)
        {
            var course = context.Courses.Find(courseLecturerDTO.CourseId);

            var lecturer = context.Lecturers.Find(courseLecturerDTO.LecturerId);

            return new CourseLecturer
            {
                Id = courseLecturerDTO.Id,
                Type = (Enums.TeachingType)courseLecturerDTO.Type,

                Course = course,
                Lecturer = lecturer
            };
        }

        public static CourseLecturerDTO ToDTO(CourseLecturer courseLecturer)
        {
            return new CourseLecturerDTO
            {
                Id = courseLecturer.Id,
                Type = (int)courseLecturer.Type,

                CourseId = courseLecturer.Course.Id,
                LecturerId = courseLecturer.Lecturer.Id
            };
        }
    }
}
