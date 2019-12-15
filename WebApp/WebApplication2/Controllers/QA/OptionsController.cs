using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;
using WebApplication2.Data;
using WebApplication2.Models;

namespace WebApplication2.Controllers.QA
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
        public async Task<ActionResult<IEnumerable<OptionModel>>> GetOptions()
        {
            return await _context.Options.ToListAsync();
        }

        // GET: api/Options/5
        [HttpGet("{id}")]
        public async Task<ActionResult<OptionModel>> GetOptionModel(int id)
        {
            var optionModel = await _context.Options.FindAsync(id);

            if (optionModel == null)
            {
                return NotFound();
            }

            return optionModel;
        }

        // PUT: api/Options/5
        [HttpPut("{id}")]
        public async Task<IActionResult> PutOptionModel(int id, OptionModel optionModel)
        {
            if (id != optionModel.Id)
            {
                return BadRequest();
            }

            _context.Entry(optionModel).State = EntityState.Modified;

            try
            {
                await _context.SaveChangesAsync();
            }
            catch (DbUpdateConcurrencyException)
            {
                if (!OptionModelExists(id))
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
        public async Task<ActionResult<OptionModel>> PostOptionModel(OptionModel optionModel)
        {
            _context.Options.Add(optionModel);
            await _context.SaveChangesAsync();

            return CreatedAtAction("GetOptionModel", new { id = optionModel.Id }, optionModel);
        }

        // DELETE: api/Options/5
        [HttpDelete("{id}")]
        public async Task<ActionResult<OptionModel>> DeleteOptionModel(int id)
        {
            var optionModel = await _context.Options.FindAsync(id);
            if (optionModel == null)
            {
                return NotFound();
            }

            _context.Options.Remove(optionModel);
            await _context.SaveChangesAsync();

            return optionModel;
        }

        private bool OptionModelExists(int id)
        {
            return _context.Options.Any(e => e.Id == id);
        }
    }
}
