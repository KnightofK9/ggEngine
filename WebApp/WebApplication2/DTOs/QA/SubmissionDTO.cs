using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

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
    }
}
