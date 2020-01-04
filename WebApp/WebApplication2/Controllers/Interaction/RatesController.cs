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
    public class RatesController : ControllerBase
    {
        private readonly ApplicationDbContext _context;

        public RatesController(ApplicationDbContext context)
        {
            _context = context;
        }

        // GET: api/Rates
        [HttpGet]
        public async Task<ActionResult<IEnumerable<RateDTO>>> GetRates()
        {
            var rateList = await _context.Rates.ToListAsync();
            var rateDTOList = new List<RateDTO>();

            foreach (var rate in rateList)
                rateDTOList.Add(RateDTO.ToDTO(rate));

            return rateDTOList;
        }

        // GET: api/Rates/5
        [HttpGet("{id}")]
        public async Task<ActionResult<RateDTO>> GetRate(int id)
        {
            var rate = await _context.Rates.FindAsync(id);

            if (rate == null)
            {
                return NotFound();
            }

            var rateDTO = RateDTO.ToDTO(rate);
            return rateDTO;
        }

        // PUT: api/Rates/5
        [HttpPut("{id}")]
        public async Task<IActionResult> PutRate(int id, RateDTO rateDTO)
        {
            var rate = RateDTO.ToModel(rateDTO, _context);

            if (id != rate.Id)
            {
                return BadRequest();
            }

            _context.Entry(rate).State = EntityState.Modified;

            try
            {
                await _context.SaveChangesAsync();
            }
            catch (DbUpdateConcurrencyException)
            {
                if (!RateExists(id))
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
        public async Task<ActionResult<RateDTO>> PostRate(RateDTO rateDTO)
        {
            var rate = RateDTO.ToModel(rateDTO, _context);

            _context.Rates.Add(rate);
            await _context.SaveChangesAsync();

            return CreatedAtAction("GetRate", new { id = rate.Id }, rateDTO);
        }

        // DELETE: api/Rates/5
        [HttpDelete("{id}")]
        public async Task<ActionResult<RateDTO>> DeleteRate(int id)
        {
            var rate = await _context.Rates.FindAsync(id);
            if (rate == null)
            {
                return NotFound();
            }

            _context.Rates.Remove(rate);
            await _context.SaveChangesAsync();

            var rateDTO = RateDTO.ToDTO(rate);
            return rateDTO;
        }

        private bool RateExists(int id)
        {
            return _context.Rates.Any(e => e.Id == id);
        }
    }
}
