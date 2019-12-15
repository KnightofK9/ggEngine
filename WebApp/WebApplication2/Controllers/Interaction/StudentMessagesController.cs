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
    public class StudentMessagesController : ControllerBase
    {
        private readonly ApplicationDbContext _context;

        public StudentMessagesController(ApplicationDbContext context)
        {
            _context = context;
        }

        // GET: api/StudentMessages
        [HttpGet]
        public async Task<ActionResult<IEnumerable<StudentMessageModel>>> GetStudentMessages()
        {
            return await _context.StudentMessages.ToListAsync();
        }

        // GET: api/StudentMessages/5
        [HttpGet("{id}")]
        public async Task<ActionResult<StudentMessageModel>> GetStudentMessageModel(int id)
        {
            var studentMessageModel = await _context.StudentMessages.FindAsync(id);

            if (studentMessageModel == null)
            {
                return NotFound();
            }

            return studentMessageModel;
        }

        // PUT: api/StudentMessages/5
        [HttpPut("{id}")]
        public async Task<IActionResult> PutStudentMessageModel(int id, StudentMessageModel studentMessageModel)
        {
            if (id != studentMessageModel.Id)
            {
                return BadRequest();
            }

            _context.Entry(studentMessageModel).State = EntityState.Modified;

            try
            {
                await _context.SaveChangesAsync();
            }
            catch (DbUpdateConcurrencyException)
            {
                if (!StudentMessageModelExists(id))
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

        // POST: api/StudentMessages
        [HttpPost]
        public async Task<ActionResult<StudentMessageModel>> PostStudentMessageModel(StudentMessageModel studentMessageModel)
        {
            _context.StudentMessages.Add(studentMessageModel);
            await _context.SaveChangesAsync();

            return CreatedAtAction("GetStudentMessageModel", new { id = studentMessageModel.Id }, studentMessageModel);
        }

        // DELETE: api/StudentMessages/5
        [HttpDelete("{id}")]
        public async Task<ActionResult<StudentMessageModel>> DeleteStudentMessageModel(int id)
        {
            var studentMessageModel = await _context.StudentMessages.FindAsync(id);
            if (studentMessageModel == null)
            {
                return NotFound();
            }

            _context.StudentMessages.Remove(studentMessageModel);
            await _context.SaveChangesAsync();

            return studentMessageModel;
        }

        private bool StudentMessageModelExists(int id)
        {
            return _context.StudentMessages.Any(e => e.Id == id);
        }
    }
}
