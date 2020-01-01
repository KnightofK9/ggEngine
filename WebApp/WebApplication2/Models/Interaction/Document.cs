using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Threading.Tasks;

namespace WebApplication2.Models
{
    public class Document
    {
        [Key]
        public int Id { get; set; }
        
        public string Name { get; set; }

        [DataType(DataType.Url)]
        public string Link { get; set; }

        #region References

        public int LessionId { get; set; }

        #endregion
    }
}
