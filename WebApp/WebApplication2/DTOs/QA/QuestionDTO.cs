using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using WebApplication2.Data;
using WebApplication2.Models;

namespace WebApplication2.DTOs
{
    public class QuestionDTO
    {
        public int Id { get; set; }

        public string Content { get; set; }

        public int Solution { get; set; }

        #region Reference

        public int TestId { get; set; }

        #endregion

        public static Question ToModel(QuestionDTO questionDTO, ApplicationDbContext context)
        {
            var optionList = new List<Option>();
            foreach (var option in context.Options)
                if (option.QuestionId == questionDTO.Id)
                    optionList.Add(option);

            return new Question
            {
                Id = questionDTO.Id,
                Content = questionDTO.Content,
                Solution = questionDTO.Solution,

                Options = optionList,

                TestId = questionDTO.TestId,
            };
        }

        public static QuestionDTO ToDTO(Question question)
        {
            return new QuestionDTO
            {
                Id = question.Id,
                Content = question.Content,
                Solution = question.Solution,

                TestId = question.TestId
            };
        }
    }
}
