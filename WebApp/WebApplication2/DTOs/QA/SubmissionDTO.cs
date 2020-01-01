using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using WebApplication2.Data;
using WebApplication2.Models;

namespace WebApplication2.DTOs
{
    public class SubmissionDTO
    {
        public int Id { get; set; }

        public string Time { get; set; }

        public int? Point { get; set; }

        #region References

        public int TestId { get; set; }
        public int StudentId { get; set; }

        #endregion

        public static Submission ToModel(SubmissionDTO submissionDTO, ApplicationDbContext context)
        {
            var answerList = new List<Answer>();
            foreach (var answer in context.Answers)
                if (answer.SubmissionId == submissionDTO.Id)
                    answerList.Add(answer);

            return new Submission
            {
                Id = submissionDTO.Id,
                Time = DateTime.Parse(submissionDTO.Time),
                Point = submissionDTO.Point,

                Answers = answerList,

                TestId = submissionDTO.TestId,
                StudentId = submissionDTO.StudentId
            };
        }

        public static SubmissionDTO ToDTO(Submission submission)
        {
            return new SubmissionDTO
            {
                Id = submission.Id,
                Time = submission.Time.ToString(),
                Point = submission.Point,

                TestId = submission.TestId,
                StudentId = submission.StudentId
            };
        }
    }
}
