using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;
using WebApplication2.DTOs;
using WebApplication2.Data;

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
        public async Task<ActionResult<IEnumerable<DocumentDTO>>> GetDocumentDTO()
        {
            return await _context.DocumentDTO.ToListAsync();
        }

        // GET: api/Documents/5
        [HttpGet("{id}")]
        public async Task<ActionResult<DocumentDTO>> GetDocumentDTO(int id)
        {
            var documentDTO = await _context.DocumentDTO.FindAsync(id);

            if (documentDTO == null)
            {
                return NotFound();
            }

            return documentDTO;
        }

        // PUT: api/Documents/5
        [HttpPut("{id}")]
        public async Task<IActionResult> PutDocumentDTO(int id, DocumentDTO documentDTO)
        {
            if (id != documentDTO.Id)
            {
                return BadRequest();
            }

            _context.Entry(documentDTO).State = EntityState.Modified;

            try
            {
                await _context.SaveChangesAsync();
            }
            catch (DbUpdateConcurrencyException)
            {
                if (!DocumentDTOExists(id))
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
        public async Task<ActionResult<DocumentDTO>> PostDocumentDTO(DocumentDTO documentDTO)
        {
            _context.DocumentDTO.Add(documentDTO);
            await _context.SaveChangesAsync();

            return CreatedAtAction("GetDocumentDTO", new { id = documentDTO.Id }, documentDTO);
        }

        // DELETE: api/Documents/5
        [HttpDelete("{id}")]
        public async Task<ActionResult<DocumentDTO>> DeleteDocumentDTO(int id)
        {
            var documentDTO = await _context.DocumentDTO.FindAsync(id);
            if (documentDTO == null)
            {
                return NotFound();
            }

            _context.DocumentDTO.Remove(documentDTO);
            await _context.SaveChangesAsync();

            return documentDTO;
        }

        private bool DocumentDTOExists(int id)
        {
            return _context.DocumentDTO.Any(e => e.Id == id);
        }
    }
}
