using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace WebApplication2.Models
{
    public class MessageStudent : Message
    {
        #region References

        public int StudentId { get; set; }

        public int DiscussionId { get; set; }

        #endregion
    }
}
