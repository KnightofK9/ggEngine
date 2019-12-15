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
    public class SubmissionsController : ControllerBase
    {
        private readonly ApplicationDbContext _context;

        public SubmissionsController(ApplicationDbContext context)
        {
            _context = context;
        }

        // GET: api/Submissions
        [HttpGet]
        public async Task<ActionResult<IEnumerable<SubmissionModel>>> GetSubmissions()
        {
            return await _context.Submissions.ToListAsync();
        }

        // GET: api/Submissions/5
        [HttpGet("{id}")]
        public async Task<ActionResult<SubmissionModel>> GetSubmissionModel(int id)
        {
            var submissionModel = await _context.Submissions.FindAsync(id);

            if (submissionModel == null)
            {
                return NotFound();
            }

            return submissionModel;
        }

        // PUT: api/Submissions/5
        [HttpPut("{id}")]
        public async Task<IActionResult> PutSubmissionModel(int id, SubmissionModel submissionModel)
        {
            if (id != submissionModel.Id)
            {
                return BadRequest();
            }

            _context.Entry(submissionModel).State = EntityState.Modified;

            try
            {
                await _context.SaveChangesAsync();
            }
            catch (DbUpdateConcurrencyException)
            {
                if (!SubmissionModelExists(id))
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
        public async Task<ActionResult<SubmissionModel>> PostSubmissionModel(SubmissionModel submissionModel)
        {
            _context.Submissions.Add(submissionModel);
            await _context.SaveChangesAsync();

            return CreatedAtAction("GetSubmissionModel", new { id = submissionModel.Id }, submissionModel);
        }

        // DELETE: api/Submissions/5
        [HttpDelete("{id}")]
        public async Task<ActionResult<SubmissionModel>> DeleteSubmissionModel(int id)
        {
            var submissionModel = await _context.Submissions.FindAsync(id);
            if (submissionModel == null)
            {
                return NotFound();
            }

            _context.Submissions.Remove(submissionModel);
            await _context.SaveChangesAsync();

            return submissionModel;
        }

        private bool SubmissionModelExists(int id)
        {
            return _context.Submissions.Any(e => e.Id == id);
        }
    }
}
