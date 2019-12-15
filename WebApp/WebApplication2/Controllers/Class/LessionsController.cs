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
    public class LessionsController : ControllerBase
    {
        private readonly ApplicationDbContext _context;

        public LessionsController(ApplicationDbContext context)
        {
            _context = context;
        }

        // GET: api/Lessions
        [HttpGet]
        public async Task<ActionResult<IEnumerable<LessionModel>>> GetLessions()
        {
            return await _context.Lessions.ToListAsync();
        }

        // GET: api/Lessions/5
        [HttpGet("{id}")]
        public async Task<ActionResult<LessionModel>> GetLessionModel(int id)
        {
            var lessionModel = await _context.Lessions.FindAsync(id);

            if (lessionModel == null)
            {
                return NotFound();
            }

            return lessionModel;
        }

        // PUT: api/Lessions/5
        [HttpPut("{id}")]
        public async Task<IActionResult> PutLessionModel(int id, LessionModel lessionModel)
        {
            if (id != lessionModel.Id)
            {
                return BadRequest();
            }

            _context.Entry(lessionModel).State = EntityState.Modified;

            try
            {
                await _context.SaveChangesAsync();
            }
            catch (DbUpdateConcurrencyException)
            {
                if (!LessionModelExists(id))
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
        public async Task<ActionResult<LessionModel>> PostLessionModel(LessionModel lessionModel)
        {
            _context.Lessions.Add(lessionModel);
            await _context.SaveChangesAsync();

            return CreatedAtAction("GetLessionModel", new { id = lessionModel.Id }, lessionModel);
        }

        // DELETE: api/Lessions/5
        [HttpDelete("{id}")]
        public async Task<ActionResult<LessionModel>> DeleteLessionModel(int id)
        {
            var lessionModel = await _context.Lessions.FindAsync(id);
            if (lessionModel == null)
            {
                return NotFound();
            }

            _context.Lessions.Remove(lessionModel);
            await _context.SaveChangesAsync();

            return lessionModel;
        }

        private bool LessionModelExists(int id)
        {
            return _context.Lessions.Any(e => e.Id == id);
        }
    }
}
