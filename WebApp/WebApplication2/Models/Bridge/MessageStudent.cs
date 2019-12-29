using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace WebApplication2.Models
{
    public class MessageStudent : Message
    {
        #region References

        public Student Student { get; set; }

        public Discussion Discussion { get; set; }

        #endregion
    }
}
