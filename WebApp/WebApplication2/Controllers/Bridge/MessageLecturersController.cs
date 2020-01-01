using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;
using WebApplication2.Data;
using WebApplication2.Models;

namespace WebApplication2.Controllers
{
    [Route("api/[controller]")]
    [ApiController]
    public class MessageLecturersController : ControllerBase
    {
        private readonly ApplicationDbContext _context;

        public MessageLecturersController(ApplicationDbContext context)
        {
            _context = context;
        }

        // GET: api/MessageLecturers
        [HttpGet]
        public async Task<ActionResult<IEnumerable<MessageLecturer>>> GetMessageLecturers()
        {
            return await _context.MessageLecturers.ToListAsync();
        }

        // GET: api/MessageLecturers/5
        [HttpGet("{id}")]
        public async Task<ActionResult<MessageLecturer>> GetMessageLecturer(int id)
        {
            var messageLecturer = await _context.MessageLecturers.FindAsync(id);

            if (messageLecturer == null)
            {
                return NotFound();
            }

            return messageLecturer;
        }

        // PUT: api/MessageLecturers/5
        [HttpPut("{id}")]
        public async Task<IActionResult> PutMessageLecturer(int id, MessageLecturer messageLecturer)
        {
            if (id != messageLecturer.Id)
            {
                return BadRequest();
            }

            _context.Entry(messageLecturer).State = EntityState.Modified;

            try
            {
                await _context.SaveChangesAsync();
            }
            catch (DbUpdateConcurrencyException)
            {
                if (!MessageLecturerExists(id))
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

        // POST: api/MessageLecturers
        [HttpPost]
        public async Task<ActionResult<MessageLecturer>> PostMessageLecturer(MessageLecturer messageLecturer)
        {
            _context.MessageLecturers.Add(messageLecturer);
            await _context.SaveChangesAsync();

            return CreatedAtAction("GetMessageLecturer", new { id = messageLecturer.Id }, messageLecturer);
        }

        // DELETE: api/MessageLecturers/5
        [HttpDelete("{id}")]
        public async Task<ActionResult<MessageLecturer>> DeleteMessageLecturer(int id)
        {
            var messageLecturer = await _context.MessageLecturers.FindAsync(id);
            if (messageLecturer == null)
            {
                return NotFound();
            }

            _context.MessageLecturers.Remove(messageLecturer);
            await _context.SaveChangesAsync();

            return messageLecturer;
        }

        private bool MessageLecturerExists(int id)
        {
            return _context.MessageLecturers.Any(e => e.Id == id);
        }
    }
}
