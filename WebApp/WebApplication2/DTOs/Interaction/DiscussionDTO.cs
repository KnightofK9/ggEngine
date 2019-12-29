using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace WebApplication2.DTOs
{
    public class DiscussionDTO
    {
        public int Id { get; set; }

        public int Status { get; set; }

        #region References

        public int LessionId { get; set; }

        #endregion
    }
}
