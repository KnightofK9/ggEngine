using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;
using WebApplication2.Data;
using WebApplication2.Models;

namespace WebApplication2.Controllers.Class
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
        public async Task<ActionResult<IEnumerable<SemesterModel>>> GetSemesters()
        {
            return await _context.Semesters.ToListAsync();
        }

        // GET: api/Semesters/5
        [HttpGet("{id}")]
        public async Task<ActionResult<SemesterModel>> GetSemesterModel(int id)
        {
            var semesterModel = await _context.Semesters.FindAsync(id);

            if (semesterModel == null)
            {
                return NotFound();
            }

            return semesterModel;
        }

        // PUT: api/Semesters/5
        [HttpPut("{id}")]
        public async Task<IActionResult> PutSemesterModel(int id, SemesterModel semesterModel)
        {
            if (id != semesterModel.Id)
            {
                return BadRequest();
            }

            _context.Entry(semesterModel).State = EntityState.Modified;

            try
            {
                await _context.SaveChangesAsync();
            }
            catch (DbUpdateConcurrencyException)
            {
                if (!SemesterModelExists(id))
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
        public async Task<ActionResult<SemesterModel>> PostSemesterModel(SemesterModel semesterModel)
        {
            _context.Semesters.Add(semesterModel);
            await _context.SaveChangesAsync();

            return CreatedAtAction("GetSemesterModel", new { id = semesterModel.Id }, semesterModel);
        }

        // DELETE: api/Semesters/5
        [HttpDelete("{id}")]
        public async Task<ActionResult<SemesterModel>> DeleteSemesterModel(int id)
        {
            var semesterModel = await _context.Semesters.FindAsync(id);
            if (semesterModel == null)
            {
                return NotFound();
            }

            _context.Semesters.Remove(semesterModel);
            await _context.SaveChangesAsync();

            return semesterModel;
        }

        private bool SemesterModelExists(int id)
        {
            return _context.Semesters.Any(e => e.Id == id);
        }
    }
}
