using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using WebApplication2.Data;
using WebApplication2.Models;

namespace WebApplication2.DTOs
{
    public class SemesterDTO
    {
        public int Id { get; set; }

        public string Name { get; set; }

        public static Semester ToModel(SemesterDTO semesterDTO, ApplicationDbContext context)
        {
            var courseList = new List<Course>();
            foreach (var course in context.Courses)
                if (course.Semester.Id == semesterDTO.Id)
                    courseList.Add(course);

            return new Semester
            {
                Id = semesterDTO.Id,
                Name = semesterDTO.Name,

                Courses = courseList
            };
        }

        public static SemesterDTO ToDTO(Semester semester)
        {
            return new SemesterDTO
            {
                Id = semester.Id,
                Name = semester.Name
            };
        }
    }
}
