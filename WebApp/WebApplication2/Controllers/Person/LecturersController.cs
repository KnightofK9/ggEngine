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
    public class LecturersController : ControllerBase
    {
        private readonly ApplicationDbContext _context;

        public LecturersController(ApplicationDbContext context)
        {
            _context = context;
        }

        // GET: api/Lecturers
        [HttpGet]
        public async Task<ActionResult<IEnumerable<LecturerDTO>>> GetLecturerDTO()
        {
            return await _context.LecturerDTO.ToListAsync();
        }

        // GET: api/Lecturers/5
        [HttpGet("{id}")]
        public async Task<ActionResult<LecturerDTO>> GetLecturerDTO(int id)
        {
            var lecturerDTO = await _context.LecturerDTO.FindAsync(id);

            if (lecturerDTO == null)
            {
                return NotFound();
            }

            return lecturerDTO;
        }

        // PUT: api/Lecturers/5
        [HttpPut("{id}")]
        public async Task<IActionResult> PutLecturerDTO(int id, LecturerDTO lecturerDTO)
        {
            if (id != lecturerDTO.Id)
            {
                return BadRequest();
            }

            _context.Entry(lecturerDTO).State = EntityState.Modified;

            try
            {
                await _context.SaveChangesAsync();
            }
            catch (DbUpdateConcurrencyException)
            {
                if (!LecturerDTOExists(id))
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

        // POST: api/Lecturers
        [HttpPost]
        public async Task<ActionResult<LecturerDTO>> PostLecturerDTO(LecturerDTO lecturerDTO)
        {
            _context.LecturerDTO.Add(lecturerDTO);
            await _context.SaveChangesAsync();

            return CreatedAtAction("GetLecturerDTO", new { id = lecturerDTO.Id }, lecturerDTO);
        }

        // DELETE: api/Lecturers/5
        [HttpDelete("{id}")]
        public async Task<ActionResult<LecturerDTO>> DeleteLecturerDTO(int id)
        {
            var lecturerDTO = await _context.LecturerDTO.FindAsync(id);
            if (lecturerDTO == null)
            {
                return NotFound();
            }

            _context.LecturerDTO.Remove(lecturerDTO);
            await _context.SaveChangesAsync();

            return lecturerDTO;
        }

        private bool LecturerDTOExists(int id)
        {
            return _context.LecturerDTO.Any(e => e.Id == id);
        }
    }
}
