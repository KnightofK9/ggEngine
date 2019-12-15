using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;
using WebApplication2.Data;
using WebApplication2.Models;

namespace WebApplication2.Controllers.Interaction
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
        public async Task<ActionResult<IEnumerable<DocumentModel>>> GetDocuments()
        {
            return await _context.Documents.ToListAsync();
        }

        // GET: api/Documents/5
        [HttpGet("{id}")]
        public async Task<ActionResult<DocumentModel>> GetDocumentModel(int id)
        {
            var documentModel = await _context.Documents.FindAsync(id);

            if (documentModel == null)
            {
                return NotFound();
            }

            return documentModel;
        }

        // PUT: api/Documents/5
        [HttpPut("{id}")]
        public async Task<IActionResult> PutDocumentModel(int id, DocumentModel documentModel)
        {
            if (id != documentModel.Id)
            {
                return BadRequest();
            }

            _context.Entry(documentModel).State = EntityState.Modified;

            try
            {
                await _context.SaveChangesAsync();
            }
            catch (DbUpdateConcurrencyException)
            {
                if (!DocumentModelExists(id))
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
        public async Task<ActionResult<DocumentModel>> PostDocumentModel(DocumentModel documentModel)
        {
            _context.Documents.Add(documentModel);
            await _context.SaveChangesAsync();

            return CreatedAtAction("GetDocumentModel", new { id = documentModel.Id }, documentModel);
        }

        // DELETE: api/Documents/5
        [HttpDelete("{id}")]
        public async Task<ActionResult<DocumentModel>> DeleteDocumentModel(int id)
        {
            var documentModel = await _context.Documents.FindAsync(id);
            if (documentModel == null)
            {
                return NotFound();
            }

            _context.Documents.Remove(documentModel);
            await _context.SaveChangesAsync();

            return documentModel;
        }

        private bool DocumentModelExists(int id)
        {
            return _context.Documents.Any(e => e.Id == id);
        }
    }
}
