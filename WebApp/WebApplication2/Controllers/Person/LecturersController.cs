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
    public class LecturersController : ControllerBase
    {
        private readonly ApplicationDbContext _context;

        public LecturersController(ApplicationDbContext context)
        {
            _context = context;
        }

        // GET: api/Lecturers
        [HttpGet]
        public async Task<ActionResult<IEnumerable<LecturerDTO>>> GetLecturers()
        {
            var lecturerList = await _context.Lecturers.ToListAsync();
            var lecturerDTOList = new List<LecturerDTO>();

            foreach (var lecturer in lecturerList)
                lecturerDTOList.Add(LecturerDTO.ToDTO(lecturer));

            return lecturerDTOList;
        }

        // GET: api/Lecturers/5
        [HttpGet("{id}")]
        public async Task<ActionResult<LecturerDTO>> GetLecturer(int id)
        {
            var lecturer = await _context.Lecturers.FindAsync(id);

            if (lecturer == null)
            {
                return NotFound();
            }

            var lecturerDTO = LecturerDTO.ToDTO(lecturer);
            return lecturerDTO;
        }

        // PUT: api/Lecturers/5
        [HttpPut("{id}")]
        public async Task<IActionResult> PutLecturer(int id, LecturerDTO lecturerDTO)
        {
            var lecturer = LecturerDTO.ToModel(lecturerDTO, _context);

            if (id != lecturer.Id)
            {
                return BadRequest();
            }

            _context.Entry(lecturer).State = EntityState.Modified;

            try
            {
                await _context.SaveChangesAsync();
            }
            catch (DbUpdateConcurrencyException)
            {
                if (!LecturerExists(id))
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
        public async Task<ActionResult<LecturerDTO>> PostLecturer(LecturerDTO lecturerDTO)
        {
            var lecturer = LecturerDTO.ToModel(lecturerDTO, _context);

            _context.Lecturers.Add(lecturer);
            await _context.SaveChangesAsync();

            return CreatedAtAction("GetLecturer", new { id = lecturer.Id }, lecturerDTO);
        }

        // DELETE: api/Lecturers/5
        [HttpDelete("{id}")]
        public async Task<ActionResult<LecturerDTO>> DeleteLecturer(int id)
        {
            var lecturer = await _context.Lecturers.FindAsync(id);
            if (lecturer == null)
            {
                return NotFound();
            }

            _context.Lecturers.Remove(lecturer);
            await _context.SaveChangesAsync();

            var lecturerDTO = LecturerDTO.ToDTO(lecturer);
            return lecturerDTO;
        }

        private bool LecturerExists(int id)
        {
            return _context.Lecturers.Any(e => e.Id == id);
        }
    }
}
