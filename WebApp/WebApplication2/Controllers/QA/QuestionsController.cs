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
    public class QuestionsController : ControllerBase
    {
        private readonly ApplicationDbContext _context;

        public QuestionsController(ApplicationDbContext context)
        {
            _context = context;
        }

        // GET: api/Questions
        [HttpGet]
        public async Task<ActionResult<IEnumerable<QuestionModel>>> GetQuestions()
        {
            return await _context.Questions.ToListAsync();
        }

        // GET: api/Questions/5
        [HttpGet("{id}")]
        public async Task<ActionResult<QuestionModel>> GetQuestionModel(int id)
        {
            var questionModel = await _context.Questions.FindAsync(id);

            if (questionModel == null)
            {
                return NotFound();
            }

            return questionModel;
        }

        // PUT: api/Questions/5
        [HttpPut("{id}")]
        public async Task<IActionResult> PutQuestionModel(int id, QuestionModel questionModel)
        {
            if (id != questionModel.Id)
            {
                return BadRequest();
            }

            _context.Entry(questionModel).State = EntityState.Modified;

            try
            {
                await _context.SaveChangesAsync();
            }
            catch (DbUpdateConcurrencyException)
            {
                if (!QuestionModelExists(id))
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

        // POST: api/Questions
        [HttpPost]
        public async Task<ActionResult<QuestionModel>> PostQuestionModel(QuestionModel questionModel)
        {
            _context.Questions.Add(questionModel);
            await _context.SaveChangesAsync();

            return CreatedAtAction("GetQuestionModel", new { id = questionModel.Id }, questionModel);
        }

        // DELETE: api/Questions/5
        [HttpDelete("{id}")]
        public async Task<ActionResult<QuestionModel>> DeleteQuestionModel(int id)
        {
            var questionModel = await _context.Questions.FindAsync(id);
            if (questionModel == null)
            {
                return NotFound();
            }

            _context.Questions.Remove(questionModel);
            await _context.SaveChangesAsync();

            return questionModel;
        }

        private bool QuestionModelExists(int id)
        {
            return _context.Questions.Any(e => e.Id == id);
        }
    }
}
