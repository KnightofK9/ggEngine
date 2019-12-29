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
    public class DiscussionsController : ControllerBase
    {
        private readonly ApplicationDbContext _context;

        public DiscussionsController(ApplicationDbContext context)
        {
            _context = context;
        }

        // GET: api/Discussions
        [HttpGet]
        public async Task<ActionResult<IEnumerable<DiscussionDTO>>> GetDiscussionDTO()
        {
            return await _context.DiscussionDTO.ToListAsync();
        }

        // GET: api/Discussions/5
        [HttpGet("{id}")]
        public async Task<ActionResult<DiscussionDTO>> GetDiscussionDTO(int id)
        {
            var discussionDTO = await _context.DiscussionDTO.FindAsync(id);

            if (discussionDTO == null)
            {
                return NotFound();
            }

            return discussionDTO;
        }

        // PUT: api/Discussions/5
        [HttpPut("{id}")]
        public async Task<IActionResult> PutDiscussionDTO(int id, DiscussionDTO discussionDTO)
        {
            if (id != discussionDTO.Id)
            {
                return BadRequest();
            }

            _context.Entry(discussionDTO).State = EntityState.Modified;

            try
            {
                await _context.SaveChangesAsync();
            }
            catch (DbUpdateConcurrencyException)
            {
                if (!DiscussionDTOExists(id))
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
        public async Task<ActionResult<DiscussionDTO>> PostDiscussionDTO(DiscussionDTO discussionDTO)
        {
            _context.DiscussionDTO.Add(discussionDTO);
            await _context.SaveChangesAsync();

            return CreatedAtAction("GetDiscussionDTO", new { id = discussionDTO.Id }, discussionDTO);
        }

        // DELETE: api/Discussions/5
        [HttpDelete("{id}")]
        public async Task<ActionResult<DiscussionDTO>> DeleteDiscussionDTO(int id)
        {
            var discussionDTO = await _context.DiscussionDTO.FindAsync(id);
            if (discussionDTO == null)
            {
                return NotFound();
            }

            _context.DiscussionDTO.Remove(discussionDTO);
            await _context.SaveChangesAsync();

            return discussionDTO;
        }

        private bool DiscussionDTOExists(int id)
        {
            return _context.DiscussionDTO.Any(e => e.Id == id);
        }
    }
}
