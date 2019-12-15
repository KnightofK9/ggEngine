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
    public class DiscussionsController : ControllerBase
    {
        private readonly ApplicationDbContext _context;

        public DiscussionsController(ApplicationDbContext context)
        {
            _context = context;
        }

        // GET: api/Discussions
        [HttpGet]
        public async Task<ActionResult<IEnumerable<DiscussionModel>>> GetDiscussions()
        {
            return await _context.Discussions.ToListAsync();
        }

        // GET: api/Discussions/5
        [HttpGet("{id}")]
        public async Task<ActionResult<DiscussionModel>> GetDiscussionModel(int id)
        {
            var discussionModel = await _context.Discussions.FindAsync(id);

            if (discussionModel == null)
            {
                return NotFound();
            }

            return discussionModel;
        }

        // PUT: api/Discussions/5
        [HttpPut("{id}")]
        public async Task<IActionResult> PutDiscussionModel(int id, DiscussionModel discussionModel)
        {
            if (id != discussionModel.Id)
            {
                return BadRequest();
            }

            _context.Entry(discussionModel).State = EntityState.Modified;

            try
            {
                await _context.SaveChangesAsync();
            }
            catch (DbUpdateConcurrencyException)
            {
                if (!DiscussionModelExists(id))
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

        // POST: api/Discussions
        [HttpPost]
        public async Task<ActionResult<DiscussionModel>> PostDiscussionModel(DiscussionModel discussionModel)
        {
            _context.Discussions.Add(discussionModel);
            await _context.SaveChangesAsync();

            return CreatedAtAction("GetDiscussionModel", new { id = discussionModel.Id }, discussionModel);
        }

        // DELETE: api/Discussions/5
        [HttpDelete("{id}")]
        public async Task<ActionResult<DiscussionModel>> DeleteDiscussionModel(int id)
        {
            var discussionModel = await _context.Discussions.FindAsync(id);
            if (discussionModel == null)
            {
                return NotFound();
            }

            _context.Discussions.Remove(discussionModel);
            await _context.SaveChangesAsync();

            return discussionModel;
        }

        private bool DiscussionModelExists(int id)
        {
            return _context.Discussions.Any(e => e.Id == id);
        }
    }
}
