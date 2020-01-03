using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using WebApplication2.Data;
using WebApplication2.Models;

namespace WebApplication2.DTOs
{
    public class MessageStudentDTO : MessageDTO
    {
        #region References

        public int StudentId { get; set; }

        public int DiscussionId { get; set; }

        #endregion

        public static MessageStudent ToModel(MessageStudentDTO messageStudentDTO, ApplicationDbContext context)
        {
            var reportList = new List<Report>();
            foreach (var report in context.Reports)
                if (report.MessageId == messageStudentDTO.Id)
                    reportList.Add(report);

            return new MessageStudent
            {
                Id = messageStudentDTO.Id,
                Time = DateTime.Parse(messageStudentDTO.Time),
                Content = messageStudentDTO.Content,

                Reports = reportList,
                
                StudentId = messageStudentDTO.StudentId,
                DiscussionId = messageStudentDTO.DiscussionId
            };
        }


        public static MessageStudentDTO ToDTO(MessageStudent messageStudent)
        {
            return new MessageStudentDTO
            {
                Id = messageStudent.Id,
                Time = messageStudent.Time.ToString(),
                Content = messageStudent.Content,

                StudentId = messageStudent.StudentId ?? 0,
                DiscussionId = messageStudent.DiscussionId ?? 0
            };
        }
    }
}
