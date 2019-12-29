using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Threading.Tasks;

namespace WebApplication2.Models
{
    public class MessageLecturer : Message
    {
        #region References

        public Lecturer Lecturer { get; set; }

        public Discussion Discussion { get; set; }

        #endregion
    }
}
