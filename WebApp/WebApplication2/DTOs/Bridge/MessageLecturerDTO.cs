using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using WebApplication2.Data;
using WebApplication2.Models;

namespace WebApplication2.DTOs
{
    public class MessageLecturerDTO : MessageDTO
    {
        #region References

        public int LecturerId { get; set; }

        public int DiscussionId { get; set; }

        #endregion

        public static MessageLecturer ToModel(MessageLecturerDTO messageLecturerDTO, ApplicationDbContext context)
        {
            var reportList = new List<Report>();
            foreach (var report in context.Reports)
                if (report.MessageId == messageLecturerDTO.Id)
                    reportList.Add(report);

            return new MessageLecturer
            {
                Id = messageLecturerDTO.Id,
                Time = DateTime.Parse(messageLecturerDTO.Time),
                Content = messageLecturerDTO.Content,

                Reports = reportList,
                
                LecturerId = messageLecturerDTO.LecturerId,
                DiscussionId = messageLecturerDTO.DiscussionId
            };
        }

        public static MessageLecturerDTO ToDTO(MessageLecturer messageLecturer)
        {
            return new MessageLecturerDTO
            {
                Id = messageLecturer.Id,
                Time = messageLecturer.Time.ToString(),
                Content = messageLecturer.Content,

                LecturerId = messageLecturer.LecturerId ?? 0,
                DiscussionId = messageLecturer.DiscussionId ?? 0
            };
        }

    }
}
