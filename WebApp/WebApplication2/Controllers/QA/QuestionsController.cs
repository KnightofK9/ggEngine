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
    public class QuestionsController : ControllerBase
    {
        private readonly ApplicationDbContext _context;

        public QuestionsController(ApplicationDbContext context)
        {
            _context = context;
        }

        // GET: api/Questions
        [HttpGet]
        public async Task<ActionResult<IEnumerable<QuestionDTO>>> GetQuestions()
        {
            var questionList = await _context.Questions.ToListAsync();
            var questionDTOList = new List<QuestionDTO>();

            foreach (var question in questionList)
                questionDTOList.Add(QuestionDTO.ToDTO(question));

            return questionDTOList;
        }

        // GET: api/Questions/5
        [HttpGet("{id}")]
        public async Task<ActionResult<QuestionDTO>> GetQuestion(int id)
        {
            var question = await _context.Questions.FindAsync(id);

            if (question == null)
            {
                return NotFound();
            }

            var questionDTO = QuestionDTO.ToDTO(question);
            return questionDTO;
        }

        // PUT: api/Questions/5
        [HttpPut("{id}")]
        public async Task<IActionResult> PutQuestion(int id, QuestionDTO questionDTO)
        {
            var question = QuestionDTO.ToModel(questionDTO, _context);

            if (id != question.Id)
            {
                return BadRequest();
            }

            _context.Entry(question).State = EntityState.Modified;

            try
            {
                await _context.SaveChangesAsync();
            }
            catch (DbUpdateConcurrencyException)
            {
                if (!QuestionExists(id))
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
        public async Task<ActionResult<QuestionDTO>> PostQuestion(QuestionDTO questionDTO)
        {
            var question = QuestionDTO.ToModel(questionDTO, _context);

            _context.Questions.Add(question);
            await _context.SaveChangesAsync();

            return CreatedAtAction("GetQuestion", new { id = question.Id }, questionDTO);
        }

        // DELETE: api/Questions/5
        [HttpDelete("{id}")]
        public async Task<ActionResult<QuestionDTO>> DeleteQuestion(int id)
        {
            var question = await _context.Questions.FindAsync(id);
            if (question == null)
            {
                return NotFound();
            }

            _context.Questions.Remove(question);
            await _context.SaveChangesAsync();

            var questionDTO = QuestionDTO.ToDTO(question);
            return questionDTO;
        }

        private bool QuestionExists(int id)
        {
            return _context.Questions.Any(e => e.Id == id);
        }

        // GET:
        [HttpGet("OfLession/{testId}")]
        public async Task<ActionResult<IEnumerable<QuestionDTO>>> GetQuestionsOfLession(int testId)
        {
            return _context.Questions.ToList()
                .FindAll(question => question.TestId == testId)
                .Select(question => QuestionDTO.ToDTO(question))
                .ToList();
        }
    }
}
