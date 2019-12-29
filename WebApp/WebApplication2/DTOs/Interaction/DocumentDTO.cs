using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace WebApplication2.DTOs
{
    public class DocumentDTO
    {
        public int Id { get; set; }

        public string Name { get; set; }

        public string Link { get; set; }

        #region References

        public int LessionId { get; set; }

        #endregion
    }
}
