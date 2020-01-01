using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using WebApplication2.Data;
using WebApplication2.Models;

namespace WebApplication2.DTOs
{
    public class LecturerDTO : PersonDTO
    {
        public string Code { get; set; }

        public int AcademicRank { get; set; }

        public static Lecturer ToModel(LecturerDTO lecturerDTO, ApplicationDbContext context)
        {
            var courseLecturerList = new List<CourseLecturer>();
            foreach (var courseLecturer in context.CourseLecturers)
                if (courseLecturer.LecturerId == lecturerDTO.Id)
                    courseLecturerList.Add(courseLecturer);

            var lessionList = new List<Lession>();
            foreach (var lession in context.Lessions)
                if (lession.LecturerId == lecturerDTO.Id)
                    lessionList.Add(lession);

            var messageLecturerList = new List<MessageLecturer>();
            foreach (var messageLecturer in context.MessageLecturers)
                if (messageLecturer.LecturerId == lecturerDTO.Id)
                    messageLecturerList.Add(messageLecturer);

            return new Lecturer
            {
                Id = lecturerDTO.Id,
                FirstName = lecturerDTO.FirstName,
                LastName = lecturerDTO.LastName,
                IsMale = lecturerDTO.IsMale,

                Code = lecturerDTO.Code,
                AcademicRank = (Enums.AcademicRank)lecturerDTO.AcademicRank,

                CourseLecturers = courseLecturerList,
                Lessions = lessionList,
                MessageLecturers = messageLecturerList,

                UserId = lecturerDTO.UserId
            };
        }

        public static LecturerDTO ToDTO(Lecturer lecturer)
        {
            return new LecturerDTO
            {
                Id = lecturer.Id,
                FirstName = lecturer.FirstName,
                LastName = lecturer.LastName,
                IsMale = lecturer.IsMale,

                Code = lecturer.Code,
                AcademicRank = (int)lecturer.AcademicRank,

                UserId = lecturer.UserId,
            };
        }
    }
}
