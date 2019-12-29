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
    public class CoursesController : ControllerBase
    {
        private readonly ApplicationDbContext _context;

        public CoursesController(ApplicationDbContext context)
        {
            _context = context;
        }

        // GET: api/Courses
        [HttpGet]
        public async Task<ActionResult<IEnumerable<CourseDTO>>> GetCourseDTO()
        {
            return await _context.CourseDTO.ToListAsync();
        }

        // GET: api/Courses/5
        [HttpGet("{id}")]
        public async Task<ActionResult<CourseDTO>> GetCourseDTO(int id)
        {
            var courseDTO = await _context.CourseDTO.FindAsync(id);

            if (courseDTO == null)
            {
                return NotFound();
            }

            return courseDTO;
        }

        // PUT: api/Courses/5
        [HttpPut("{id}")]
        public async Task<IActionResult> PutCourseDTO(int id, CourseDTO courseDTO)
        {
            if (id != courseDTO.Id)
            {
                return BadRequest();
            }

            _context.Entry(courseDTO).State = EntityState.Modified;

            try
            {
                await _context.SaveChangesAsync();
            }
            catch (DbUpdateConcurrencyException)
            {
                if (!CourseDTOExists(id))
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

        // POST: api/Courses
        [HttpPost]
        public async Task<ActionResult<CourseDTO>> PostCourseDTO(CourseDTO courseDTO)
        {
            _context.CourseDTO.Add(courseDTO);
            await _context.SaveChangesAsync();

            return CreatedAtAction("GetCourseDTO", new { id = courseDTO.Id }, courseDTO);
        }

        // DELETE: api/Courses/5
        [HttpDelete("{id}")]
        public async Task<ActionResult<CourseDTO>> DeleteCourseDTO(int id)
        {
            var courseDTO = await _context.CourseDTO.FindAsync(id);
            if (courseDTO == null)
            {
                return NotFound();
            }

            _context.CourseDTO.Remove(courseDTO);
            await _context.SaveChangesAsync();

            return courseDTO;
        }

        private bool CourseDTOExists(int id)
        {
            return _context.CourseDTO.Any(e => e.Id == id);
        }
    }
}
