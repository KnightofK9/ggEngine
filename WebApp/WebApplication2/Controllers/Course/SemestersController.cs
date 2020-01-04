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
    public class SemestersController : ControllerBase
    {
        private readonly ApplicationDbContext _context;

        public SemestersController(ApplicationDbContext context)
        {
            _context = context;
        }

        // GET: api/Semesters
        [HttpGet]
        public async Task<ActionResult<IEnumerable<SemesterDTO>>> GetSemesters()
        {
            var semesterList = await _context.Semesters.ToListAsync();
            var semesterDTOList = new List<SemesterDTO>();

            foreach (var semester in semesterList)
                semesterDTOList.Add(SemesterDTO.ToDTO(semester));

            return semesterDTOList;
        }

        // GET: api/Semesters/5
        [HttpGet("{id}")]
        public async Task<ActionResult<SemesterDTO>> GetSemester(int id)
        {
            var semester = await _context.Semesters.FindAsync(id);

            if (semester == null)
            {
                return NotFound();
            }

            var semesterDTO = SemesterDTO.ToDTO(semester);
            return semesterDTO;
        }

        // PUT: api/Semesters/5
        [HttpPut("{id}")]
        public async Task<IActionResult> PutSemester(int id, SemesterDTO semesterDTO)
        {
            var semester = SemesterDTO.ToModel(semesterDTO, _context);

            if (id != semester.Id)
            {
                return BadRequest();
            }

            _context.Entry(semester).State = EntityState.Modified;

            try
            {
                await _context.SaveChangesAsync();
            }
            catch (DbUpdateConcurrencyException)
            {
                if (!SemesterExists(id))
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
        public async Task<ActionResult<SemesterDTO>> PostSemester(SemesterDTO semesterDTO)
        {
            var semester = SemesterDTO.ToModel(semesterDTO, _context);

            _context.Semesters.Add(semester);
            await _context.SaveChangesAsync();

            return CreatedAtAction("GetSemester", new { id = semester.Id }, semesterDTO);
        }

        // DELETE: api/Semesters/5
        [HttpDelete("{id}")]
        public async Task<ActionResult<SemesterDTO>> DeleteSemester(int id)
        {
            var semester = await _context.Semesters.FindAsync(id);
            if (semester == null)
            {
                return NotFound();
            }

            _context.Semesters.Remove(semester);
            await _context.SaveChangesAsync();

            var semesterDTO = SemesterDTO.ToDTO(semester);
            return semesterDTO;
        }

        private bool SemesterExists(int id)
        {
            return _context.Semesters.Any(e => e.Id == id);
        }
    }
}
