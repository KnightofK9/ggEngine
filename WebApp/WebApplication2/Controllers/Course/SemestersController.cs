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
    public class SemestersController : ControllerBase
    {
        private readonly ApplicationDbContext _context;

        public SemestersController(ApplicationDbContext context)
        {
            _context = context;
        }

        // GET: api/Semesters
        [HttpGet]
        public async Task<ActionResult<IEnumerable<SemesterDTO>>> GetSemesterDTO()
        {
            return await _context.SemesterDTO.ToListAsync();
        }

        // GET: api/Semesters/5
        [HttpGet("{id}")]
        public async Task<ActionResult<SemesterDTO>> GetSemesterDTO(int id)
        {
            var semesterDTO = await _context.SemesterDTO.FindAsync(id);

            if (semesterDTO == null)
            {
                return NotFound();
            }

            return semesterDTO;
        }

        // PUT: api/Semesters/5
        [HttpPut("{id}")]
        public async Task<IActionResult> PutSemesterDTO(int id, SemesterDTO semesterDTO)
        {
            if (id != semesterDTO.Id)
            {
                return BadRequest();
            }

            _context.Entry(semesterDTO).State = EntityState.Modified;

            try
            {
                await _context.SaveChangesAsync();
            }
            catch (DbUpdateConcurrencyException)
            {
                if (!SemesterDTOExists(id))
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

        // POST: api/Semesters
        [HttpPost]
        public async Task<ActionResult<SemesterDTO>> PostSemesterDTO(SemesterDTO semesterDTO)
        {
            _context.SemesterDTO.Add(semesterDTO);
            await _context.SaveChangesAsync();

            return CreatedAtAction("GetSemesterDTO", new { id = semesterDTO.Id }, semesterDTO);
        }

        // DELETE: api/Semesters/5
        [HttpDelete("{id}")]
        public async Task<ActionResult<SemesterDTO>> DeleteSemesterDTO(int id)
        {
            var semesterDTO = await _context.SemesterDTO.FindAsync(id);
            if (semesterDTO == null)
            {
                return NotFound();
            }

            _context.SemesterDTO.Remove(semesterDTO);
            await _context.SaveChangesAsync();

            return semesterDTO;
        }

        private bool SemesterDTOExists(int id)
        {
            return _context.SemesterDTO.Any(e => e.Id == id);
        }
    }
}
