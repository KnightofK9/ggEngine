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
    public class CourseStudentsController : ControllerBase
    {
        private readonly ApplicationDbContext _context;

        public CourseStudentsController(ApplicationDbContext context)
        {
            _context = context;
        }

        // GET: api/CourseStudents
        [HttpGet]
        public async Task<ActionResult<IEnumerable<CourseStudentDTO>>> GetCourseStudentDTO()
        {
            return await _context.CourseStudentDTO.ToListAsync();
        }

        // GET: api/CourseStudents/5
        [HttpGet("{id}")]
        public async Task<ActionResult<CourseStudentDTO>> GetCourseStudentDTO(int id)
        {
            var courseStudentDTO = await _context.CourseStudentDTO.FindAsync(id);

            if (courseStudentDTO == null)
            {
                return NotFound();
            }

            return courseStudentDTO;
        }

        // PUT: api/CourseStudents/5
        [HttpPut("{id}")]
        public async Task<IActionResult> PutCourseStudentDTO(int id, CourseStudentDTO courseStudentDTO)
        {
            if (id != courseStudentDTO.Id)
            {
                return BadRequest();
            }

            _context.Entry(courseStudentDTO).State = EntityState.Modified;

            try
            {
                await _context.SaveChangesAsync();
            }
            catch (DbUpdateConcurrencyException)
            {
                if (!CourseStudentDTOExists(id))
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

        // POST: api/CourseStudents
        [HttpPost]
        public async Task<ActionResult<CourseStudentDTO>> PostCourseStudentDTO(CourseStudentDTO courseStudentDTO)
        {
            _context.CourseStudentDTO.Add(courseStudentDTO);
            await _context.SaveChangesAsync();

            return CreatedAtAction("GetCourseStudentDTO", new { id = courseStudentDTO.Id }, courseStudentDTO);
        }

        // DELETE: api/CourseStudents/5
        [HttpDelete("{id}")]
        public async Task<ActionResult<CourseStudentDTO>> DeleteCourseStudentDTO(int id)
        {
            var courseStudentDTO = await _context.CourseStudentDTO.FindAsync(id);
            if (courseStudentDTO == null)
            {
                return NotFound();
            }

            _context.CourseStudentDTO.Remove(courseStudentDTO);
            await _context.SaveChangesAsync();

            return courseStudentDTO;
        }

        private bool CourseStudentDTOExists(int id)
        {
            return _context.CourseStudentDTO.Any(e => e.Id == id);
        }
    }
}
