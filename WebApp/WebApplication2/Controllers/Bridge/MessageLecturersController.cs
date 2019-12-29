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
    public class MessageLecturersController : ControllerBase
    {
        private readonly ApplicationDbContext _context;

        public MessageLecturersController(ApplicationDbContext context)
        {
            _context = context;
        }

        // GET: api/MessageLecturers
        [HttpGet]
        public async Task<ActionResult<IEnumerable<MessageLecturerDTO>>> GetMessageLecturerDTO()
        {
            return await _context.MessageLecturerDTO.ToListAsync();
        }

        // GET: api/MessageLecturers/5
        [HttpGet("{id}")]
        public async Task<ActionResult<MessageLecturerDTO>> GetMessageLecturerDTO(int id)
        {
            var messageLecturerDTO = await _context.MessageLecturerDTO.FindAsync(id);

            if (messageLecturerDTO == null)
            {
                return NotFound();
            }

            return messageLecturerDTO;
        }

        // PUT: api/MessageLecturers/5
        [HttpPut("{id}")]
        public async Task<IActionResult> PutMessageLecturerDTO(int id, MessageLecturerDTO messageLecturerDTO)
        {
            if (id != messageLecturerDTO.Id)
            {
                return BadRequest();
            }

            _context.Entry(messageLecturerDTO).State = EntityState.Modified;

            try
            {
                await _context.SaveChangesAsync();
            }
            catch (DbUpdateConcurrencyException)
            {
                if (!MessageLecturerDTOExists(id))
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
        public async Task<ActionResult<MessageLecturerDTO>> PostMessageLecturerDTO(MessageLecturerDTO messageLecturerDTO)
        {
            _context.MessageLecturerDTO.Add(messageLecturerDTO);
            await _context.SaveChangesAsync();

            return CreatedAtAction("GetMessageLecturerDTO", new { id = messageLecturerDTO.Id }, messageLecturerDTO);
        }

        // DELETE: api/MessageLecturers/5
        [HttpDelete("{id}")]
        public async Task<ActionResult<MessageLecturerDTO>> DeleteMessageLecturerDTO(int id)
        {
            var messageLecturerDTO = await _context.MessageLecturerDTO.FindAsync(id);
            if (messageLecturerDTO == null)
            {
                return NotFound();
            }

            _context.MessageLecturerDTO.Remove(messageLecturerDTO);
            await _context.SaveChangesAsync();

            return messageLecturerDTO;
        }

        private bool MessageLecturerDTOExists(int id)
        {
            return _context.MessageLecturerDTO.Any(e => e.Id == id);
        }
    }
}
