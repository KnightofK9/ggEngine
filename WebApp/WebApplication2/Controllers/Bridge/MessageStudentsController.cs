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
    public class MessageStudentsController : ControllerBase
    {
        private readonly ApplicationDbContext _context;

        public MessageStudentsController(ApplicationDbContext context)
        {
            _context = context;
        }

        // GET: api/MessageStudents
        [HttpGet]
        public async Task<ActionResult<IEnumerable<MessageStudentDTO>>> GetMessageStudents()
        {
            var messageStudentList = await _context.MessageStudents.ToListAsync();
            var messageStudentDTOList = new List<MessageStudentDTO>();

            foreach (var messageStudent in messageStudentList)
                messageStudentDTOList.Add(MessageStudentDTO.ToDTO(messageStudent));

            return messageStudentDTOList;
        }

        // GET: api/MessageStudents/5
        [HttpGet("{id}")]
        public async Task<ActionResult<MessageStudentDTO>> GetMessageStudent(int id)
        {
            var messageStudent = await _context.MessageStudents.FindAsync(id);

            if (messageStudent == null)
            {
                return NotFound();
            }

            var messageStudentDTO = MessageStudentDTO.ToDTO(messageStudent);
            return messageStudentDTO;
        }

        // PUT: api/MessageStudents/5
        [HttpPut("{id}")]
        public async Task<IActionResult> PutMessageStudent(int id, MessageStudentDTO messageStudentDTO)
        {
            var messageStudent = MessageStudentDTO.ToModel(messageStudentDTO, _context);

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
        public async Task<ActionResult<MessageStudentDTO>> PostMessageStudent(MessageStudentDTO messageStudentDTO)
        {
            var messageStudent = MessageStudentDTO.ToModel(messageStudentDTO, _context);
            
            _context.MessageStudents.Add(messageStudent);
            await _context.SaveChangesAsync();

            return CreatedAtAction("GetMessageStudent", new { id = messageStudent.Id }, messageStudentDTO);
        }

        // DELETE: api/MessageStudents/5
        [HttpDelete("{id}")]
        public async Task<ActionResult<MessageStudentDTO>> DeleteMessageStudent(int id)
        {
            var messageStudent = await _context.MessageStudents.FindAsync(id);
            if (messageStudent == null)
            {
                return NotFound();
            }

            _context.MessageStudents.Remove(messageStudent);
            await _context.SaveChangesAsync();

            var messageStudentDTO = MessageStudentDTO.ToDTO(messageStudent);
            return messageStudentDTO;
        }

        private bool MessageStudentExists(int id)
        {
            return _context.MessageStudents.Any(e => e.Id == id);
        }

        // GET:
        [HttpGet("OfDiscussion/{dicussionId}")]
        public async Task<ActionResult<IEnumerable<MessageStudentDTO>>> GetMessageStudentsOfDiscussion(int dicussionId)
        {
            return _context.MessageStudents.ToList()
                .FindAll(message => message.DiscussionId == dicussionId)
                .Select(message => MessageStudentDTO.ToDTO(message))
                .ToList();
        }
    }
}
