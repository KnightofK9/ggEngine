using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

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
    }
}
