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
    public class LessionsController : ControllerBase
    {
        private readonly ApplicationDbContext _context;

        public LessionsController(ApplicationDbContext context)
        {
            _context = context;
        }

        // GET: api/Lessions
        [HttpGet]
        public async Task<ActionResult<IEnumerable<LessionDTO>>> GetLessions()
        {
            var lessionList = await _context.Lessions.ToListAsync();
            var lessionDTOList = new List<LessionDTO>();

            foreach (var lession in lessionList)
                lessionDTOList.Add(LessionDTO.ToDTO(lession));

            return lessionDTOList;
        }

        // GET: api/Lessions/5
        [HttpGet("{id}")]
        public async Task<ActionResult<LessionDTO>> GetLession(int id)
        {
            var lession = await _context.Lessions.FindAsync(id);

            if (lession == null)
            {
                return NotFound();
            }

            var lessionDTO = LessionDTO.ToDTO(lession);
            return lessionDTO;
        }

        // PUT: api/Lessions/5
        [HttpPut("{id}")]
        public async Task<IActionResult> PutLession(int id, LessionDTO lessionDTO)
        {
            var lession = LessionDTO.ToModel(lessionDTO, _context);

            if (id != lession.Id)
            {
                return BadRequest();
            }

            _context.Entry(lession).State = EntityState.Modified;

            try
            {
                await _context.SaveChangesAsync();
            }
            catch (DbUpdateConcurrencyException)
            {
                if (!LessionExists(id))
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

        // POST: api/Lessions
        [HttpPost]
        public async Task<ActionResult<LessionDTO>> PostLession(LessionDTO lessionDTO)
        {
            var lession = LessionDTO.ToModel(lessionDTO, _context);

            _context.Lessions.Add(lession);
            await _context.SaveChangesAsync();

            return CreatedAtAction("GetLession", new { id = lession.Id }, lessionDTO);
        }

        // DELETE: api/Lessions/5
        [HttpDelete("{id}")]
        public async Task<ActionResult<LessionDTO>> DeleteLession(int id)
        {
            var lession = await _context.Lessions.FindAsync(id);
            if (lession == null)
            {
                return NotFound();
            }

            _context.Lessions.Remove(lession);
            await _context.SaveChangesAsync();

            var lessionDTO = LessionDTO.ToDTO(lession);
            return lessionDTO;
        }

        private bool LessionExists(int id)
        {
            return _context.Lessions.Any(e => e.Id == id);
        }

        // GET:
        [HttpGet("OfCourse/{courseId}")]
        public async Task<ActionResult<IEnumerable<LessionDTO>>> GetLessionsOfCourse(int courseId)
        {
            return _context.Lessions.ToList()
                .FindAll(lession => lession.CourseId == courseId)
                .Select(lession => LessionDTO.ToDTO(lession))
                .ToList();
        }
    }
}
