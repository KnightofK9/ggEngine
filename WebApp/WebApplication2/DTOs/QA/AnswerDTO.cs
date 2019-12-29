using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace WebApplication2.DTO
{
    public class AnswerDTO
    {
        public int Id { get; set; }

        public int QuestionId { get; set; }

        public int SelectionId { get; set; }

        #region References

        public int SubmissionId { get; set; }

        #endregion
    }
}
