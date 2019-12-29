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
    public class MessageStudentsController : ControllerBase
    {
        private readonly ApplicationDbContext _context;

        public MessageStudentsController(ApplicationDbContext context)
        {
            _context = context;
        }

        // GET: api/MessageStudents
        [HttpGet]
        public async Task<ActionResult<IEnumerable<MessageStudentDTO>>> GetMessageStudentDTO()
        {
            return await _context.MessageStudentDTO.ToListAsync();
        }

        // GET: api/MessageStudents/5
        [HttpGet("{id}")]
        public async Task<ActionResult<MessageStudentDTO>> GetMessageStudentDTO(int id)
        {
            var messageStudentDTO = await _context.MessageStudentDTO.FindAsync(id);

            if (messageStudentDTO == null)
            {
                return NotFound();
            }

            return messageStudentDTO;
        }

        // PUT: api/MessageStudents/5
        [HttpPut("{id}")]
        public async Task<IActionResult> PutMessageStudentDTO(int id, MessageStudentDTO messageStudentDTO)
        {
            if (id != messageStudentDTO.Id)
            {
                return BadRequest();
            }

            _context.Entry(messageStudentDTO).State = EntityState.Modified;

            try
            {
                await _context.SaveChangesAsync();
            }
            catch (DbUpdateConcurrencyException)
            {
                if (!MessageStudentDTOExists(id))
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

        // POST: api/MessageStudents
        [HttpPost]
        public async Task<ActionResult<MessageStudentDTO>> PostMessageStudentDTO(MessageStudentDTO messageStudentDTO)
        {
            _context.MessageStudentDTO.Add(messageStudentDTO);
            await _context.SaveChangesAsync();

            return CreatedAtAction("GetMessageStudentDTO", new { id = messageStudentDTO.Id }, messageStudentDTO);
        }

        // DELETE: api/MessageStudents/5
        [HttpDelete("{id}")]
        public async Task<ActionResult<MessageStudentDTO>> DeleteMessageStudentDTO(int id)
        {
            var messageStudentDTO = await _context.MessageStudentDTO.FindAsync(id);
            if (messageStudentDTO == null)
            {
                return NotFound();
            }

            _context.MessageStudentDTO.Remove(messageStudentDTO);
            await _context.SaveChangesAsync();

            return messageStudentDTO;
        }

        private bool MessageStudentDTOExists(int id)
        {
            return _context.MessageStudentDTO.Any(e => e.Id == id);
        }
    }
}
