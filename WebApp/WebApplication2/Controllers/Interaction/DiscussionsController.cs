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
    public class DiscussionsController : ControllerBase
    {
        private readonly ApplicationDbContext _context;

        public DiscussionsController(ApplicationDbContext context)
        {
            _context = context;
        }

        // GET: api/Discussions
        [HttpGet]
        public async Task<ActionResult<IEnumerable<DiscussionDTO>>> GetDiscussions()
        {
            var discussionList = await _context.Discussions.ToListAsync();
            var discussionDTOList = new List<DiscussionDTO>();

            foreach (var discussion in discussionList)
                discussionDTOList.Add(DiscussionDTO.ToDTO(discussion));

            return discussionDTOList;
        }

        // GET: api/Discussions/5
        [HttpGet("{id}")]
        public async Task<ActionResult<DiscussionDTO>> GetDiscussion(int id)
        {
            var discussion = await _context.Discussions.FindAsync(id);

            if (discussion == null)
            {
                return NotFound();
            }

            var discussionDTO = DiscussionDTO.ToDTO(discussion);
            return discussionDTO;
        }

        // PUT: api/Discussions/5
        [HttpPut("{id}")]
        public async Task<IActionResult> PutDiscussion(int id, DiscussionDTO discussionDTO)
        {
            var discussion = DiscussionDTO.ToModel(discussionDTO, _context);

            if (id != discussion.Id)
            {
                return BadRequest();
            }

            _context.Entry(discussion).State = EntityState.Modified;

            try
            {
                await _context.SaveChangesAsync();
            }
            catch (DbUpdateConcurrencyException)
            {
                if (!DiscussionExists(id))
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
        public async Task<ActionResult<DiscussionDTO>> PostDiscussion(DiscussionDTO discussionDTO)
        {
            var discussion = DiscussionDTO.ToModel(discussionDTO, _context);

            _context.Discussions.Add(discussion);
            await _context.SaveChangesAsync();

            return CreatedAtAction("GetDiscussion", new { id = discussion.Id }, discussionDTO);
        }

        // DELETE: api/Discussions/5
        [HttpDelete("{id}")]
        public async Task<ActionResult<DiscussionDTO>> DeleteDiscussion(int id)
        {
            var discussion = await _context.Discussions.FindAsync(id);
            if (discussion == null)
            {
                return NotFound();
            }

            _context.Discussions.Remove(discussion);
            await _context.SaveChangesAsync();

            var discussionDTO = DiscussionDTO.ToDTO(discussion);
            return discussionDTO;
        }

        private bool DiscussionExists(int id)
        {
            return _context.Discussions.Any(e => e.Id == id);
        }

        // GET:
        [HttpGet("OfLession/{lessionId}")]
        public async Task<ActionResult<IEnumerable<DiscussionDTO>>> GetDiscussionsOfLession(int lessionId)
        {
            return _context.Discussions.ToList()
                .FindAll(discussion => discussion.LessionId == lessionId)
                .Select(discussion => DiscussionDTO.ToDTO(discussion))
                .ToList();
        }
    }
}
