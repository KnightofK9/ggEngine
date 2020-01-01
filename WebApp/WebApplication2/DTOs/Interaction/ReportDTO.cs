using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using WebApplication2.Data;
using WebApplication2.Models;

namespace WebApplication2.DTOs
{
    public class ReportDTO
    {
        public int Id { get; set; }

        public string Comment { get; set; }

        #region References

        public int StudentId { get; set; }

        public int MessageId { get; set; }

        #endregion

        public static Report ToModel(ReportDTO reportDTO, ApplicationDbContext context)
        {
            return new Report
            {
                Id = reportDTO.Id,
                Comment = reportDTO.Comment,

                StudentId = reportDTO.StudentId,
                MessageId = reportDTO.MessageId
            };
        }

        public static ReportDTO ToDTO(Report report)
        {
            return new ReportDTO
            {
                Id = report.Id,
                Comment = report.Comment,
                
                StudentId = report.StudentId,
                MessageId = report.MessageId
            };
        }
    }    
}
