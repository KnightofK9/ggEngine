using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using WebApplication2.Data;
using WebApplication2.Models;

namespace WebApplication2.DTOs
{
    public class OptionDTO
    {
        public int Id { get; set; }

        public string Content { get; set; }

        #region References

        public int QuestionId { get; set; }

        #endregion

        public static Option ToModel(OptionDTO optionDTO, ApplicationDbContext context)
        {
            return new Option
            {
                Id = optionDTO.Id,
                Content = optionDTO.Content,

                QuestionId = optionDTO.QuestionId
            };
        }

        public static OptionDTO ToDTO(Option option)
        {
            return new OptionDTO
            {
                Id = option.Id,
                Content = option.Content,

                QuestionId = option.QuestionId
            };
        }
    }
}
