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
    public class CourseLecturersController : ControllerBase
    {
        private readonly ApplicationDbContext _context;

        public CourseLecturersController(ApplicationDbContext context)
        {
            _context = context;
        }

        // GET: api/CourseLecturers
        [HttpGet]
        public async Task<ActionResult<IEnumerable<CourseLecturerDTO>>> GetCourseLecturers()
        {
            var courseLecturerList = await _context.CourseLecturers.ToListAsync();
            var courseLecturerDTOList = new List<CourseLecturerDTO>();

            foreach (var courseLecturer in courseLecturerList)
                courseLecturerDTOList.Add(CourseLecturerDTO.ToDTO(courseLecturer));

            return courseLecturerDTOList;
        }

        // GET: api/CourseLecturers/5
        [HttpGet("{id}")]
        public async Task<ActionResult<CourseLecturerDTO>> GetCourseLecturer(int id)
        {
            var courseLecturer = await _context.CourseLecturers.FindAsync(id);

            if (courseLecturer == null)
            {
                return NotFound();
            }

            var courseLecturerDTO = CourseLecturerDTO.ToDTO(courseLecturer);
            return courseLecturerDTO;
        }

        // PUT: api/CourseLecturers/5
        [HttpPut("{id}")]
        public async Task<IActionResult> PutCourseLecturer(int id, CourseLecturerDTO courseLecturerDTO)
        {
            var courseLecturer = CourseLecturerDTO.ToModel(courseLecturerDTO, _context);

            if (id != courseLecturer.Id)
            {
                return BadRequest();
            }

            _context.Entry(courseLecturer).State = EntityState.Modified;

            try
            {
                await _context.SaveChangesAsync();
            }
            catch (DbUpdateConcurrencyException)
            {
                if (!CourseLecturerExists(id))
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
        public async Task<ActionResult<CourseLecturerDTO>> PostCourseLecturer(CourseLecturerDTO courseLecturerDTO)
        {
            var courseLecturer = CourseLecturerDTO.ToModel(courseLecturerDTO, _context);

            _context.CourseLecturers.Add(courseLecturer);
            await _context.SaveChangesAsync();

            return CreatedAtAction("GetCourseLecturer", new { id = courseLecturer.Id }, courseLecturerDTO);
        }

        // DELETE: api/CourseLecturers/5
        [HttpDelete("{id}")]
        public async Task<ActionResult<CourseLecturerDTO>> DeleteCourseLecturer(int id)
        {
            var courseLecturer = await _context.CourseLecturers.FindAsync(id);
            if (courseLecturer == null)
            {
                return NotFound();
            }

            _context.CourseLecturers.Remove(courseLecturer);
            await _context.SaveChangesAsync();

            var courseLecturerDTO = CourseLecturerDTO.ToDTO(courseLecturer);
            return courseLecturerDTO;
        }

        private bool CourseLecturerExists(int id)
        {
            return _context.CourseLecturers.Any(e => e.Id == id);
        }
    }
}
