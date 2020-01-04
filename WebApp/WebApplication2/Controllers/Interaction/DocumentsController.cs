using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;
using WebApplication2.Data;
using WebApplication2.DTOs;
using WebApplication2.Models;

namespace WebApplication2.Controllers
{
    [Route("api/[controller]")]
    [ApiController]
    public class DocumentsController : ControllerBase
    {
        private readonly ApplicationDbContext _context;

        public DocumentsController(ApplicationDbContext context)
        {
            _context = context;
        }

        // GET: api/Documents
        [HttpGet]
        public async Task<ActionResult<IEnumerable<DocumentDTO>>> GetDocuments()
        {
            var documentList = await _context.Documents.ToListAsync();
            var documentDTOList = new List<DocumentDTO>();

            foreach (var document in documentList)
                documentDTOList.Add(DocumentDTO.ToDTO(document));

            return documentDTOList;
        }

        // GET: api/Documents/5
        [HttpGet("{id}")]
        public async Task<ActionResult<DocumentDTO>> GetDocument(int id)
        {
            var document = await _context.Documents.FindAsync(id);

            if (document == null)
            {
                return NotFound();
            }

            var documentDTO = DocumentDTO.ToDTO(document);
            return documentDTO;
        }

        // PUT: api/Documents/5
        [HttpPut("{id}")]
        public async Task<IActionResult> PutDocument(int id, DocumentDTO documentDTO)
        {
            var document = DocumentDTO.ToModel(documentDTO, _context);

            if (id != document.Id)
            {
                return BadRequest();
            }

            _context.Entry(document).State = EntityState.Modified;

            try
            {
                await _context.SaveChangesAsync();
            }
            catch (DbUpdateConcurrencyException)
            {
                if (!DocumentExists(id))
                {
                    return NotFound();
                }
                else
                {
                    throw;
                }
            }

            return NoContent();
        }

        // POST: api/Documents
        [HttpPost]
        public async Task<ActionResult<DocumentDTO>> PostDocument(DocumentDTO documentDTO)
        {
            var document = DocumentDTO.ToModel(documentDTO, _context);

            _context.Documents.Add(document);
            await _context.SaveChangesAsync();

            return CreatedAtAction("GetDocument", new { id = document.Id }, documentDTO);
        }

        // DELETE: api/Documents/5
        [HttpDelete("{id}")]
        public async Task<ActionResult<DocumentDTO>> DeleteDocument(int id)
        {
            var document = await _context.Documents.FindAsync(id);
            if (document == null)
            {
                return NotFound();
            }

            _context.Documents.Remove(document);
            await _context.SaveChangesAsync();

            var documentDTO = DocumentDTO.ToDTO(document);
            return documentDTO;
        }

        private bool DocumentExists(int id)
        {
            return _context.Documents.Any(e => e.Id == id);
        }

        // GET:
        [HttpGet("OfCourse/{courseId}")]
        public async Task<ActionResult<IEnumerable<DocumentDTO>>> GetDocumentsOfCourse(int courseId)
        {
            return _context.Documents.ToList()
                .FindAll(document => document.CourseId == courseId)
                .Select(document => DocumentDTO.ToDTO(document))
                .ToList();
        }
    }
}
