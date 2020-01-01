using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using WebApplication2.Data;
using WebApplication2.Models;

namespace WebApplication2.DTOs
{
    public class AnswerDTO
    {
        public int Id { get; set; }

        public int QuestionId { get; set; }

        public int SelectionId { get; set; }

        #region References

        public int SubmissionId { get; set; }

        #endregion

        public static Answer ToModel(AnswerDTO answerDTO, ApplicationDbContext context)
        {
            return new Answer
            {
                Id = answerDTO.Id,
                QuestionId = answerDTO.QuestionId,
                SelectionId = answerDTO.SelectionId,

                SubmissionId = answerDTO.SubmissionId
            };
        }

        public static AnswerDTO ToDTO(Answer answer)
        {
            return new AnswerDTO
            {
                Id = answer.Id,
                QuestionId = answer.QuestionId,
                SelectionId = answer.SelectionId,

                SubmissionId = answer.SubmissionId
            };
        }
    }
}
