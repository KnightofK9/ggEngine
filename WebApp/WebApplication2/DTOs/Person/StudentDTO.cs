using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using WebApplication2.Data;
using WebApplication2.Models;

namespace WebApplication2.DTOs
{
    public class StudentDTO : PersonDTO
    {
        public string Code { get; set; }

        public string NickName { get; set; }

        public bool Anonymous { get; set; }

        public static Student ToModel(StudentDTO studentDTO, ApplicationDbContext context)
        {
            var attendanceList = new List<Attendance>();
            foreach (var attendance in context.Attendances)
                if (attendance.Student.Id == studentDTO.Id)
                    attendanceList.Add(attendance);

            var courseStudentList = new List<CourseStudent>();
            foreach (var courseStudent in context.CourseStudents)
                if (courseStudent.Student.Id == studentDTO.Id)
                    courseStudentList.Add(courseStudent);

            var messageStudentList = new List<MessageStudent>();
            foreach (var messageStudent in context.MessageStudents)
                if (messageStudent.Student.Id == studentDTO.Id)
                    messageStudentList.Add(messageStudent);

            var rateList = new List<Rate>();
            foreach (var rate in context.Rates)
                if (rate.Student.Id == studentDTO.Id)
                    rateList.Add(rate);

            var reportList = new List<Report>();
            foreach (var report in context.Reports)
                if (report.Student.Id == studentDTO.Id)
                    reportList.Add(report);

            var submisstionList = new List<Submission>();
            foreach (var submisstion in submisstionList)
                if (submisstion.Student.Id == studentDTO.Id)
                    submisstionList.Add(submisstion);

            var user = context.Users.Find(studentDTO.UserId);

            return new Student
            {
                Id = studentDTO.Id,
                FirstName = studentDTO.FirstName,
                LastName = studentDTO.LastName,
                IsMale = studentDTO.IsMale,

                Code = studentDTO.Code,
                NickName = studentDTO.NickName,
                Anonymous = studentDTO.Anonymous,

                Attendances = attendanceList,
                CourseStudents = courseStudentList,
                MessageStudents = messageStudentList,
                Rates = rateList,
                Reports = reportList,
                Submissions = submisstionList,         

                User = user,
            };
        }

        public static StudentDTO ToDTO(Student student)
        {
            return new StudentDTO
            {
                Id = student.Id,
                FirstName = student.FirstName,
                LastName = student.LastName,
                IsMale = student.IsMale,

                Code = student.Code,
                NickName = student.NickName,
                Anonymous = student.Anonymous,

                UserId = student.User.Id,
            };
        }
    }
}
