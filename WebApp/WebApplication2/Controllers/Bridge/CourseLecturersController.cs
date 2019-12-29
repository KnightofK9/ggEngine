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
    public class CourseLecturersController : ControllerBase
    {
        private readonly ApplicationDbContext _context;

        public CourseLecturersController(ApplicationDbContext context)
        {
            _context = context;
        }

        // GET: api/CourseLecturers
        [HttpGet]
        public async Task<ActionResult<IEnumerable<CourseLecturerDTO>>> GetCourseLecturerDTO()
        {
            return await _context.CourseLecturerDTO.ToListAsync();
        }

        // GET: api/CourseLecturers/5
        [HttpGet("{id}")]
        public async Task<ActionResult<CourseLecturerDTO>> GetCourseLecturerDTO(int id)
        {
            var courseLecturerDTO = await _context.CourseLecturerDTO.FindAsync(id);

            if (courseLecturerDTO == null)
            {
                return NotFound();
            }

            return courseLecturerDTO;
        }

        // PUT: api/CourseLecturers/5
        [HttpPut("{id}")]
        public async Task<IActionResult> PutCourseLecturerDTO(int id, CourseLecturerDTO courseLecturerDTO)
        {
            if (id != courseLecturerDTO.Id)
            {
                return BadRequest();
            }

            _context.Entry(courseLecturerDTO).State = EntityState.Modified;

            try
            {
                await _context.SaveChangesAsync();
            }
            catch (DbUpdateConcurrencyException)
            {
                if (!CourseLecturerDTOExists(id))
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

        // POST: api/CourseLecturers
        [HttpPost]
        public async Task<ActionResult<CourseLecturerDTO>> PostCourseLecturerDTO(CourseLecturerDTO courseLecturerDTO)
        {
            _context.CourseLecturerDTO.Add(courseLecturerDTO);
            await _context.SaveChangesAsync();

            return CreatedAtAction("GetCourseLecturerDTO", new { id = courseLecturerDTO.Id }, courseLecturerDTO);
        }

        // DELETE: api/CourseLecturers/5
        [HttpDelete("{id}")]
        public async Task<ActionResult<CourseLecturerDTO>> DeleteCourseLecturerDTO(int id)
        {
            var courseLecturerDTO = await _context.CourseLecturerDTO.FindAsync(id);
            if (courseLecturerDTO == null)
            {
                return NotFound();
            }

            _context.CourseLecturerDTO.Remove(courseLecturerDTO);
            await _context.SaveChangesAsync();

            return courseLecturerDTO;
        }

        private bool CourseLecturerDTOExists(int id)
        {
            return _context.CourseLecturerDTO.Any(e => e.Id == id);
        }
    }
}
