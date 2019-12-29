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
    public class SubmissionsController : ControllerBase
    {
        private readonly ApplicationDbContext _context;

        public SubmissionsController(ApplicationDbContext context)
        {
            _context = context;
        }

        // GET: api/Submissions
        [HttpGet]
        public async Task<ActionResult<IEnumerable<SubmissionDTO>>> GetSubmissionDTO()
        {
            return await _context.SubmissionDTO.ToListAsync();
        }

        // GET: api/Submissions/5
        [HttpGet("{id}")]
        public async Task<ActionResult<SubmissionDTO>> GetSubmissionDTO(int id)
        {
            var submissionDTO = await _context.SubmissionDTO.FindAsync(id);

            if (submissionDTO == null)
            {
                return NotFound();
            }

            return submissionDTO;
        }

        // PUT: api/Submissions/5
        [HttpPut("{id}")]
        public async Task<IActionResult> PutSubmissionDTO(int id, SubmissionDTO submissionDTO)
        {
            if (id != submissionDTO.Id)
            {
                return BadRequest();
            }

            _context.Entry(submissionDTO).State = EntityState.Modified;

            try
            {
                await _context.SaveChangesAsync();
            }
            catch (DbUpdateConcurrencyException)
            {
                if (!SubmissionDTOExists(id))
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

        // POST: api/Submissions
        [HttpPost]
        public async Task<ActionResult<SubmissionDTO>> PostSubmissionDTO(SubmissionDTO submissionDTO)
        {
            _context.SubmissionDTO.Add(submissionDTO);
            await _context.SaveChangesAsync();

            return CreatedAtAction("GetSubmissionDTO", new { id = submissionDTO.Id }, submissionDTO);
        }

        // DELETE: api/Submissions/5
        [HttpDelete("{id}")]
        public async Task<ActionResult<SubmissionDTO>> DeleteSubmissionDTO(int id)
        {
            var submissionDTO = await _context.SubmissionDTO.FindAsync(id);
            if (submissionDTO == null)
            {
                return NotFound();
            }

            _context.SubmissionDTO.Remove(submissionDTO);
            await _context.SaveChangesAsync();

            return submissionDTO;
        }

        private bool SubmissionDTOExists(int id)
        {
            return _context.SubmissionDTO.Any(e => e.Id == id);
        }
    }
}
