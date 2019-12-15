using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;
using WebApplication2.Data;
using WebApplication2.Models;

namespace WebApplication2.Controllers.Interaction
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
        public async Task<ActionResult<IEnumerable<RateModel>>> GetRates()
        {
            return await _context.Rates.ToListAsync();
        }

        // GET: api/Rates/5
        [HttpGet("{id}")]
        public async Task<ActionResult<RateModel>> GetRateModel(int id)
        {
            var rateModel = await _context.Rates.FindAsync(id);

            if (rateModel == null)
            {
                return NotFound();
            }

            return rateModel;
        }

        // PUT: api/Rates/5
        [HttpPut("{id}")]
        public async Task<IActionResult> PutRateModel(int id, RateModel rateModel)
        {
            if (id != rateModel.Id)
            {
                return BadRequest();
            }

            _context.Entry(rateModel).State = EntityState.Modified;

            try
            {
                await _context.SaveChangesAsync();
            }
            catch (DbUpdateConcurrencyException)
            {
                if (!RateModelExists(id))
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
        public async Task<ActionResult<RateModel>> PostRateModel(RateModel rateModel)
        {
            _context.Rates.Add(rateModel);
            await _context.SaveChangesAsync();

            return CreatedAtAction("GetRateModel", new { id = rateModel.Id }, rateModel);
        }

        // DELETE: api/Rates/5
        [HttpDelete("{id}")]
        public async Task<ActionResult<RateModel>> DeleteRateModel(int id)
        {
            var rateModel = await _context.Rates.FindAsync(id);
            if (rateModel == null)
            {
                return NotFound();
            }

            _context.Rates.Remove(rateModel);
            await _context.SaveChangesAsync();

            return rateModel;
        }

        private bool RateModelExists(int id)
        {
            return _context.Rates.Any(e => e.Id == id);
        }
    }
}
