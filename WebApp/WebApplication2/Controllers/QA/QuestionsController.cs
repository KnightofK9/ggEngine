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
    public class QuestionsController : ControllerBase
    {
        private readonly ApplicationDbContext _context;

        public QuestionsController(ApplicationDbContext context)
        {
            _context = context;
        }

        // GET: api/Questions
        [HttpGet]
        public async Task<ActionResult<IEnumerable<QuestionDTO>>> GetQuestionDTO()
        {
            return await _context.QuestionDTO.ToListAsync();
        }

        // GET: api/Questions/5
        [HttpGet("{id}")]
        public async Task<ActionResult<QuestionDTO>> GetQuestionDTO(int id)
        {
            var questionDTO = await _context.QuestionDTO.FindAsync(id);

            if (questionDTO == null)
            {
                return NotFound();
            }

            return questionDTO;
        }

        // PUT: api/Questions/5
        [HttpPut("{id}")]
        public async Task<IActionResult> PutQuestionDTO(int id, QuestionDTO questionDTO)
        {
            if (id != questionDTO.Id)
            {
                return BadRequest();
            }

            _context.Entry(questionDTO).State = EntityState.Modified;

            try
            {
                await _context.SaveChangesAsync();
            }
            catch (DbUpdateConcurrencyException)
            {
                if (!QuestionDTOExists(id))
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
        public async Task<ActionResult<QuestionDTO>> PostQuestionDTO(QuestionDTO questionDTO)
        {
            _context.QuestionDTO.Add(questionDTO);
            await _context.SaveChangesAsync();

            return CreatedAtAction("GetQuestionDTO", new { id = questionDTO.Id }, questionDTO);
        }

        // DELETE: api/Questions/5
        [HttpDelete("{id}")]
        public async Task<ActionResult<QuestionDTO>> DeleteQuestionDTO(int id)
        {
            var questionDTO = await _context.QuestionDTO.FindAsync(id);
            if (questionDTO == null)
            {
                return NotFound();
            }

            _context.QuestionDTO.Remove(questionDTO);
            await _context.SaveChangesAsync();

            return questionDTO;
        }

        private bool QuestionDTOExists(int id)
        {
            return _context.QuestionDTO.Any(e => e.Id == id);
        }
    }
}
