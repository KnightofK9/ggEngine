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
    public class OptionsController : ControllerBase
    {
        private readonly ApplicationDbContext _context;

        public OptionsController(ApplicationDbContext context)
        {
            _context = context;
        }

        // GET: api/Options
        [HttpGet]
        public async Task<ActionResult<IEnumerable<OptionDTO>>> GetOptionDTO()
        {
            return await _context.OptionDTO.ToListAsync();
        }

        // GET: api/Options/5
        [HttpGet("{id}")]
        public async Task<ActionResult<OptionDTO>> GetOptionDTO(int id)
        {
            var optionDTO = await _context.OptionDTO.FindAsync(id);

            if (optionDTO == null)
            {
                return NotFound();
            }

            return optionDTO;
        }

        // PUT: api/Options/5
        [HttpPut("{id}")]
        public async Task<IActionResult> PutOptionDTO(int id, OptionDTO optionDTO)
        {
            if (id != optionDTO.Id)
            {
                return BadRequest();
            }

            _context.Entry(optionDTO).State = EntityState.Modified;

            try
            {
                await _context.SaveChangesAsync();
            }
            catch (DbUpdateConcurrencyException)
            {
                if (!OptionDTOExists(id))
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

        // POST: api/Options
        [HttpPost]
        public async Task<ActionResult<OptionDTO>> PostOptionDTO(OptionDTO optionDTO)
        {
            _context.OptionDTO.Add(optionDTO);
            await _context.SaveChangesAsync();

            return CreatedAtAction("GetOptionDTO", new { id = optionDTO.Id }, optionDTO);
        }

        // DELETE: api/Options/5
        [HttpDelete("{id}")]
        public async Task<ActionResult<OptionDTO>> DeleteOptionDTO(int id)
        {
            var optionDTO = await _context.OptionDTO.FindAsync(id);
            if (optionDTO == null)
            {
                return NotFound();
            }

            _context.OptionDTO.Remove(optionDTO);
            await _context.SaveChangesAsync();

            return optionDTO;
        }

        private bool OptionDTOExists(int id)
        {
            return _context.OptionDTO.Any(e => e.Id == id);
        }
    }
}
