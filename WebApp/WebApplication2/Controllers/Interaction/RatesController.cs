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
    public class RatesController : ControllerBase
    {
        private readonly ApplicationDbContext _context;

        public RatesController(ApplicationDbContext context)
        {
            _context = context;
        }

        // GET: api/Rates
        [HttpGet]
        public async Task<ActionResult<IEnumerable<RateDTO>>> GetRateDTO()
        {
            return await _context.RateDTO.ToListAsync();
        }

        // GET: api/Rates/5
        [HttpGet("{id}")]
        public async Task<ActionResult<RateDTO>> GetRateDTO(int id)
        {
            var rateDTO = await _context.RateDTO.FindAsync(id);

            if (rateDTO == null)
            {
                return NotFound();
            }

            return rateDTO;
        }

        // PUT: api/Rates/5
        [HttpPut("{id}")]
        public async Task<IActionResult> PutRateDTO(int id, RateDTO rateDTO)
        {
            if (id != rateDTO.Id)
            {
                return BadRequest();
            }

            _context.Entry(rateDTO).State = EntityState.Modified;

            try
            {
                await _context.SaveChangesAsync();
            }
            catch (DbUpdateConcurrencyException)
            {
                if (!RateDTOExists(id))
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

        // POST: api/Rates
        [HttpPost]
        public async Task<ActionResult<RateDTO>> PostRateDTO(RateDTO rateDTO)
        {
            _context.RateDTO.Add(rateDTO);
            await _context.SaveChangesAsync();

            return CreatedAtAction("GetRateDTO", new { id = rateDTO.Id }, rateDTO);
        }

        // DELETE: api/Rates/5
        [HttpDelete("{id}")]
        public async Task<ActionResult<RateDTO>> DeleteRateDTO(int id)
        {
            var rateDTO = await _context.RateDTO.FindAsync(id);
            if (rateDTO == null)
            {
                return NotFound();
            }

            _context.RateDTO.Remove(rateDTO);
            await _context.SaveChangesAsync();

            return rateDTO;
        }

        private bool RateDTOExists(int id)
        {
            return _context.RateDTO.Any(e => e.Id == id);
        }
    }
}
