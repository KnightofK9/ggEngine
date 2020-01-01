using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection.Metadata;
using System.Threading.Tasks;
using WebApplication2.Data;

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

        public static Document ToModel(DocumentDTO documentDTO, ApplicationDbContext context)
        {
            return new Document
            {

            };
        }
    }
}
