using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection.Metadata;
using System.Threading.Tasks;
using WebApplication2.Data;
using WebApplication2.Models;
using Document = WebApplication2.Models.Document;

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
                Id = documentDTO.Id,
                Name = documentDTO.Name,
                Link = documentDTO.Link,

                LessionId = documentDTO.LessionId
            };
        }

        public static DocumentDTO ToDTO(Document document)
        {
            return new DocumentDTO
            {
                Id = document.Id,
                Name = document.Name,
                Link = document.Link,

                LessionId = document.LessionId
            };
        }
    }
}
