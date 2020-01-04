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
    public class MessageLecturersController : ControllerBase
    {
        private readonly ApplicationDbContext _context;

        public MessageLecturersController(ApplicationDbContext context)
        {
            _context = context;
        }

        // GET: api/MessageLecturers
        [HttpGet]
        public async Task<ActionResult<IEnumerable<MessageLecturerDTO>>> GetMessageLecturers()
        {
            var messageLecturerList = await _context.MessageLecturers.ToListAsync();
            var messageLecturerDTOList = new List<MessageLecturerDTO>();

            foreach (var messageLecturer in messageLecturerList)
                messageLecturerDTOList.Add(MessageLecturerDTO.ToDTO(messageLecturer));

            return messageLecturerDTOList;
        }

        // GET: api/MessageLecturers/5
        [HttpGet("{id}")]
        public async Task<ActionResult<MessageLecturerDTO>> GetMessageLecturer(int id)
        {
            var messageLecturer = await _context.MessageLecturers.FindAsync(id);

            if (messageLecturer == null)
            {
                return NotFound();
            }

            var messageLecturerDTO = MessageLecturerDTO.ToDTO(messageLecturer);
            return messageLecturerDTO;
        }

        // PUT: api/MessageLecturers/5
        [HttpPut("{id}")]
        public async Task<IActionResult> PutMessageLecturer(int id, MessageLecturerDTO messageLecturerDTO)
        {
            var messageLecturer = MessageLecturerDTO.ToModel(messageLecturerDTO, _context);

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
        public async Task<ActionResult<MessageLecturerDTO>> PostMessageLecturer(MessageLecturerDTO messageLecturerDTO)
        {
            var messageLecturer = MessageLecturerDTO.ToModel(messageLecturerDTO, _context);

            _context.MessageLecturers.Add(messageLecturer);
            await _context.SaveChangesAsync();

            return CreatedAtAction("GetMessageLecturer", new { id = messageLecturer.Id }, messageLecturerDTO);
        }

        // DELETE: api/MessageLecturers/5
        [HttpDelete("{id}")]
        public async Task<ActionResult<MessageLecturerDTO>> DeleteMessageLecturer(int id)
        {
            var messageLecturer = await _context.MessageLecturers.FindAsync(id);
            if (messageLecturer == null)
            {
                return NotFound();
            }

            _context.MessageLecturers.Remove(messageLecturer);
            await _context.SaveChangesAsync();

            var messageLecturerDTO = MessageLecturerDTO.ToDTO(messageLecturer);
            return messageLecturerDTO;
        }

        private bool MessageLecturerExists(int id)
        {
            return _context.MessageLecturers.Any(e => e.Id == id);
        }

        // GET:
        [HttpGet("OfDiscussion/{dicussionId}")]
        public async Task<ActionResult<IEnumerable<MessageLecturerDTO>>> GetMessageLecturersOfDiscussion(int dicussionId)
        {
            return _context.MessageLecturers.ToList()
                .FindAll(message => message.DiscussionId == dicussionId)
                .Select(message => MessageLecturerDTO.ToDTO(message))
                .ToList();
        }
    }
}
