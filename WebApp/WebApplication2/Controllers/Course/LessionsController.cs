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
    public class LessionsController : ControllerBase
    {
        private readonly ApplicationDbContext _context;

        public LessionsController(ApplicationDbContext context)
        {
            _context = context;
        }

        // GET: api/Lessions
        [HttpGet]
        public async Task<ActionResult<IEnumerable<LessionDTO>>> GetLessionDTO()
        {
            return await _context.LessionDTO.ToListAsync();
        }

        // GET: api/Lessions/5
        [HttpGet("{id}")]
        public async Task<ActionResult<LessionDTO>> GetLessionDTO(int id)
        {
            var lessionDTO = await _context.LessionDTO.FindAsync(id);

            if (lessionDTO == null)
            {
                return NotFound();
            }

            return lessionDTO;
        }

        // PUT: api/Lessions/5
        [HttpPut("{id}")]
        public async Task<IActionResult> PutLessionDTO(int id, LessionDTO lessionDTO)
        {
            if (id != lessionDTO.Id)
            {
                return BadRequest();
            }

            _context.Entry(lessionDTO).State = EntityState.Modified;

            try
            {
                await _context.SaveChangesAsync();
            }
            catch (DbUpdateConcurrencyException)
            {
                if (!LessionDTOExists(id))
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
        public async Task<ActionResult<LessionDTO>> PostLessionDTO(LessionDTO lessionDTO)
        {
            _context.LessionDTO.Add(lessionDTO);
            await _context.SaveChangesAsync();

            return CreatedAtAction("GetLessionDTO", new { id = lessionDTO.Id }, lessionDTO);
        }

        // DELETE: api/Lessions/5
        [HttpDelete("{id}")]
        public async Task<ActionResult<LessionDTO>> DeleteLessionDTO(int id)
        {
            var lessionDTO = await _context.LessionDTO.FindAsync(id);
            if (lessionDTO == null)
            {
                return NotFound();
            }

            _context.LessionDTO.Remove(lessionDTO);
            await _context.SaveChangesAsync();

            return lessionDTO;
        }

        private bool LessionDTOExists(int id)
        {
            return _context.LessionDTO.Any(e => e.Id == id);
        }
    }
}
