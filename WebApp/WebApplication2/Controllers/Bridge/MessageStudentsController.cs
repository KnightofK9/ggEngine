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
    public class MessageStudentsController : ControllerBase
    {
        private readonly ApplicationDbContext _context;

        public MessageStudentsController(ApplicationDbContext context)
        {
            _context = context;
        }

        // GET: api/MessageStudents
        [HttpGet]
        public async Task<ActionResult<IEnumerable<MessageStudent>>> GetMessageStudents()
        {
            return await _context.MessageStudents.ToListAsync();
        }

        // GET: api/MessageStudents/5
        [HttpGet("{id}")]
        public async Task<ActionResult<MessageStudent>> GetMessageStudent(int id)
        {
            var messageStudent = await _context.MessageStudents.FindAsync(id);

            if (messageStudent == null)
            {
                return NotFound();
            }

            return messageStudent;
        }

        // PUT: api/MessageStudents/5
        [HttpPut("{id}")]
        public async Task<IActionResult> PutMessageStudent(int id, MessageStudent messageStudent)
        {
            if (id != messageStudent.Id)
            {
                return BadRequest();
            }

            _context.Entry(messageStudent).State = EntityState.Modified;

            try
            {
                await _context.SaveChangesAsync();
            }
            catch (DbUpdateConcurrencyException)
            {
                if (!MessageStudentExists(id))
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
        public async Task<ActionResult<MessageStudent>> PostMessageStudent(MessageStudent messageStudent)
        {
            _context.MessageStudents.Add(messageStudent);
            await _context.SaveChangesAsync();

            return CreatedAtAction("GetMessageStudent", new { id = messageStudent.Id }, messageStudent);
        }

        // DELETE: api/MessageStudents/5
        [HttpDelete("{id}")]
        public async Task<ActionResult<MessageStudent>> DeleteMessageStudent(int id)
        {
            var messageStudent = await _context.MessageStudents.FindAsync(id);
            if (messageStudent == null)
            {
                return NotFound();
            }

            _context.MessageStudents.Remove(messageStudent);
            await _context.SaveChangesAsync();

            return messageStudent;
        }

        private bool MessageStudentExists(int id)
        {
            return _context.MessageStudents.Any(e => e.Id == id);
        }
    }
}
