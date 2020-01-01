using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using WebApplication2.Data;
using WebApplication2.Models;

namespace WebApplication2.DTOs
{
    public class DiscussionDTO
    {
        public int Id { get; set; }

        public int Status { get; set; }

        #region References

        public int LessionId { get; set; }

        #endregion

        public static Discussion ToModel(DiscussionDTO discussionDTO, ApplicationDbContext context)
        {
            var messageLecturerList = new List<MessageLecturer>();
            foreach (var messageLecturer in context.MessageLecturers)
                if (messageLecturer.DiscussionId == discussionDTO.Id)
                    messageLecturerList.Add(messageLecturer);

            var messageStudentList = new List<MessageStudent>();
            foreach (var messageStudent in context.MessageStudents)
                if (messageStudent.DiscussionId == discussionDTO.Id)
                    messageStudentList.Add(messageStudent);

            var lession = context.Lessions.Find(discussionDTO.LessionId);

            return new Discussion
            {
                Id = discussionDTO.Id,
                Status = (Enums.DiscusstionStatus)discussionDTO.Status,
                
                MessageLecturers = messageLecturerList,
                MessageStudents = messageStudentList,

                LessionId = lession.Id
            };
        }

        public static DiscussionDTO ToDTO(Discussion discussion)
        {
            return new DiscussionDTO
            {
                Id = discussion.Id,
                Status = (int)discussion.Status,

                LessionId = discussion.LessionId
            };
        }
    }
}
