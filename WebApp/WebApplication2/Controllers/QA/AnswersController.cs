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
    public class AnswersController : ControllerBase
    {
        private readonly ApplicationDbContext _context;

        public AnswersController(ApplicationDbContext context)
        {
            _context = context;
        }

        // GET: api/Answers
        [HttpGet]
        public async Task<ActionResult<IEnumerable<AnswerModel>>> GetAnswers()
        {
            return await _context.Answers.ToListAsync();
        }

        // GET: api/Answers/5
        [HttpGet("{id}")]
        public async Task<ActionResult<AnswerModel>> GetAnswerModel(int id)
        {
            var answerModel = await _context.Answers.FindAsync(id);

            if (answerModel == null)
            {
                return NotFound();
            }

            return answerModel;
        }

        // PUT: api/Answers/5
        [HttpPut("{id}")]
        public async Task<IActionResult> PutAnswerModel(int id, AnswerModel answerModel)
        {
            if (id != answerModel.Id)
            {
                return BadRequest();
            }

            _context.Entry(answerModel).State = EntityState.Modified;

            try
            {
                await _context.SaveChangesAsync();
            }
            catch (DbUpdateConcurrencyException)
            {
                if (!AnswerModelExists(id))
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

        // POST: api/Answers
        [HttpPost]
        public async Task<ActionResult<AnswerModel>> PostAnswerModel(AnswerModel answerModel)
        {
            _context.Answers.Add(answerModel);
            await _context.SaveChangesAsync();

            return CreatedAtAction("GetAnswerModel", new { id = answerModel.Id }, answerModel);
        }

        // DELETE: api/Answers/5
        [HttpDelete("{id}")]
        public async Task<ActionResult<AnswerModel>> DeleteAnswerModel(int id)
        {
            var answerModel = await _context.Answers.FindAsync(id);
            if (answerModel == null)
            {
                return NotFound();
            }

            _context.Answers.Remove(answerModel);
            await _context.SaveChangesAsync();

            return answerModel;
        }

        private bool AnswerModelExists(int id)
        {
            return _context.Answers.Any(e => e.Id == id);
        }
    }
}
