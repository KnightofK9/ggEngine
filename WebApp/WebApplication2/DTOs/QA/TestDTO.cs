using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using WebApplication2.Data;
using WebApplication2.Models;

namespace WebApplication2.DTOs
{
    public class TestDTO
    {
        public int Id { get; set; }

        public string Title { get; set; }

        public string Deadline { get; set; }

        public int Status { get; set; }

        #region References

        public int LessionId { get; set; }

        #endregion

        public static Test ToModel(TestDTO testDTO, ApplicationDbContext context)
        {
            var questionList = new List<Question>();
            foreach (var question in context.Questions)
                if (question.TestId == testDTO.Id)
                    questionList.Add(question);

            var submissionList = new List<Submission>();
            foreach (var submission in context.Submissions)
                if (submission.TestId == testDTO.Id)
                    submissionList.Add(submission);

            return new Test
            {
                Id = testDTO.Id,
                Title = testDTO.Title,
                Deadline = DateTime.Parse(testDTO.Deadline),
                Status = (Enums.DiscusstionStatus)testDTO.Status,

                Questions = questionList,
                Submissions = submissionList,

                LessionId = testDTO.LessionId
            };
        }

        public static TestDTO ToDTO(Test test)
        {
            return new TestDTO
            {
                Id = test.Id,
                Title = test.Title,
                Deadline = test.Deadline.ToString(),
                Status = (int)test.Status,
                
                LessionId = test.LessionId
            };
        }
    }
}
