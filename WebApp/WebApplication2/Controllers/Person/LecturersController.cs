using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;
using WebApplication2.Data;
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
        public async Task<ActionResult<IEnumerable<LecturerModel>>> GetLecturers()
        {
            return await _context.Lecturers.ToListAsync();
        }

        // GET: api/Lecturers/5
        [HttpGet("{id}")]
        public async Task<ActionResult<LecturerModel>> GetLecturerModel(int id)
        {
            var lecturerModel = await _context.Lecturers.FindAsync(id);

            if (lecturerModel == null)
            {
                return NotFound();
            }

            return lecturerModel;
        }

        // PUT: api/Lecturers/5
        [HttpPut("{id}")]
        public async Task<IActionResult> PutLecturerModel(int id, LecturerModel lecturerModel)
        {
            if (id != lecturerModel.Id)
            {
                return BadRequest();
            }

            _context.Entry(lecturerModel).State = EntityState.Modified;

            try
            {
                await _context.SaveChangesAsync();
            }
            catch (DbUpdateConcurrencyException)
            {
                if (!LecturerModelExists(id))
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
        public async Task<ActionResult<LecturerModel>> PostLecturerModel(LecturerModel lecturerModel)
        {
            _context.Lecturers.Add(lecturerModel);
            await _context.SaveChangesAsync();

            return CreatedAtAction("GetLecturerModel", new { id = lecturerModel.Id }, lecturerModel);
        }

        // DELETE: api/Lecturers/5
        [HttpDelete("{id}")]
        public async Task<ActionResult<LecturerModel>> DeleteLecturerModel(int id)
        {
            var lecturerModel = await _context.Lecturers.FindAsync(id);
            if (lecturerModel == null)
            {
                return NotFound();
            }

            _context.Lecturers.Remove(lecturerModel);
            await _context.SaveChangesAsync();

            return lecturerModel;
        }

        private bool LecturerModelExists(int id)
        {
            return _context.Lecturers.Any(e => e.Id == id);
        }
    }
}
