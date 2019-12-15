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
    public class LecturerMessagesController : ControllerBase
    {
        private readonly ApplicationDbContext _context;

        public LecturerMessagesController(ApplicationDbContext context)
        {
            _context = context;
        }

        // GET: api/LecturerMessages
        [HttpGet]
        public async Task<ActionResult<IEnumerable<LecturerMessageModel>>> GetLecturerMessages()
        {
            return await _context.LecturerMessages.ToListAsync();
        }

        // GET: api/LecturerMessages/5
        [HttpGet("{id}")]
        public async Task<ActionResult<LecturerMessageModel>> GetLecturerMessageModel(int id)
        {
            var lecturerMessageModel = await _context.LecturerMessages.FindAsync(id);

            if (lecturerMessageModel == null)
            {
                return NotFound();
            }

            return lecturerMessageModel;
        }

        // PUT: api/LecturerMessages/5
        [HttpPut("{id}")]
        public async Task<IActionResult> PutLecturerMessageModel(int id, LecturerMessageModel lecturerMessageModel)
        {
            if (id != lecturerMessageModel.Id)
            {
                return BadRequest();
            }

            _context.Entry(lecturerMessageModel).State = EntityState.Modified;

            try
            {
                await _context.SaveChangesAsync();
            }
            catch (DbUpdateConcurrencyException)
            {
                if (!LecturerMessageModelExists(id))
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

        // POST: api/LecturerMessages
        [HttpPost]
        public async Task<ActionResult<LecturerMessageModel>> PostLecturerMessageModel(LecturerMessageModel lecturerMessageModel)
        {
            _context.LecturerMessages.Add(lecturerMessageModel);
            await _context.SaveChangesAsync();

            return CreatedAtAction("GetLecturerMessageModel", new { id = lecturerMessageModel.Id }, lecturerMessageModel);
        }

        // DELETE: api/LecturerMessages/5
        [HttpDelete("{id}")]
        public async Task<ActionResult<LecturerMessageModel>> DeleteLecturerMessageModel(int id)
        {
            var lecturerMessageModel = await _context.LecturerMessages.FindAsync(id);
            if (lecturerMessageModel == null)
            {
                return NotFound();
            }

            _context.LecturerMessages.Remove(lecturerMessageModel);
            await _context.SaveChangesAsync();

            return lecturerMessageModel;
        }

        private bool LecturerMessageModelExists(int id)
        {
            return _context.LecturerMessages.Any(e => e.Id == id);
        }
    }
}
