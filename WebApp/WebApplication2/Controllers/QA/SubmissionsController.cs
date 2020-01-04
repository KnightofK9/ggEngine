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
    public class SubmissionsController : ControllerBase
    {
        private readonly ApplicationDbContext _context;

        public SubmissionsController(ApplicationDbContext context)
        {
            _context = context;
        }

        // GET: api/Submissions
        [HttpGet]
        public async Task<ActionResult<IEnumerable<SubmissionDTO>>> GetSubmissions()
        {
            var submissionList = await _context.Submissions.ToListAsync();
            var submissionDTOList = new List<SubmissionDTO>();

            foreach (var submission in submissionList)
                submissionDTOList.Add(SubmissionDTO.ToDTO(submission));

            return submissionDTOList;
        }

        // GET: api/Submissions/5
        [HttpGet("{id}")]
        public async Task<ActionResult<SubmissionDTO>> GetSubmission(int id)
        {
            var submission = await _context.Submissions.FindAsync(id);

            if (submission == null)
            {
                return NotFound();
            }

            var submissionDTO = SubmissionDTO.ToDTO(submission);
            return submissionDTO;
        }

        // PUT: api/Submissions/5
        [HttpPut("{id}")]
        public async Task<IActionResult> PutSubmission(int id, SubmissionDTO submissionDTO)
        {
            var submission = SubmissionDTO.ToModel(submissionDTO, _context);

            if (id != submission.Id)
            {
                return BadRequest();
            }

            _context.Entry(submission).State = EntityState.Modified;

            try
            {
                await _context.SaveChangesAsync();
            }
            catch (DbUpdateConcurrencyException)
            {
                if (!SubmissionExists(id))
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
        public async Task<ActionResult<SubmissionDTO>> PostSubmission(SubmissionDTO submissionDTO)
        {
            var submission = SubmissionDTO.ToModel(submissionDTO, _context);

            _context.Submissions.Add(submission);
            await _context.SaveChangesAsync();

            return CreatedAtAction("GetSubmission", new { id = submission.Id }, submissionDTO);
        }

        // DELETE: api/Submissions/5
        [HttpDelete("{id}")]
        public async Task<ActionResult<SubmissionDTO>> DeleteSubmission(int id)
        {
            var submission = await _context.Submissions.FindAsync(id);
            if (submission == null)
            {
                return NotFound();
            }

            _context.Submissions.Remove(submission);
            await _context.SaveChangesAsync();

            var submissionDTO = SubmissionDTO.ToDTO(submission);
            return submissionDTO;
        }

        private bool SubmissionExists(int id)
        {
            return _context.Submissions.Any(e => e.Id == id);
        }
    }
}
