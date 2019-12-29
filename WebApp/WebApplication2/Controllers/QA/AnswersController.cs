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
    public class AnswersController : ControllerBase
    {
        private readonly ApplicationDbContext _context;

        public AnswersController(ApplicationDbContext context)
        {
            _context = context;
        }

        // GET: api/Answers
        [HttpGet]
        public async Task<ActionResult<IEnumerable<AnswerDTO>>> GetAnswerDTO()
        {
            return await _context.AnswerDTO.ToListAsync();
        }

        // GET: api/Answers/5
        [HttpGet("{id}")]
        public async Task<ActionResult<AnswerDTO>> GetAnswerDTO(int id)
        {
            var answerDTO = await _context.AnswerDTO.FindAsync(id);

            if (answerDTO == null)
            {
                return NotFound();
            }

            return answerDTO;
        }

        // PUT: api/Answers/5
        [HttpPut("{id}")]
        public async Task<IActionResult> PutAnswerDTO(int id, AnswerDTO answerDTO)
        {
            if (id != answerDTO.Id)
            {
                return BadRequest();
            }

            _context.Entry(answerDTO).State = EntityState.Modified;

            try
            {
                await _context.SaveChangesAsync();
            }
            catch (DbUpdateConcurrencyException)
            {
                if (!AnswerDTOExists(id))
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
        public async Task<ActionResult<AnswerDTO>> PostAnswerDTO(AnswerDTO answerDTO)
        {
            _context.AnswerDTO.Add(answerDTO);
            await _context.SaveChangesAsync();

            return CreatedAtAction("GetAnswerDTO", new { id = answerDTO.Id }, answerDTO);
        }

        // DELETE: api/Answers/5
        [HttpDelete("{id}")]
        public async Task<ActionResult<AnswerDTO>> DeleteAnswerDTO(int id)
        {
            var answerDTO = await _context.AnswerDTO.FindAsync(id);
            if (answerDTO == null)
            {
                return NotFound();
            }

            _context.AnswerDTO.Remove(answerDTO);
            await _context.SaveChangesAsync();

            return answerDTO;
        }

        private bool AnswerDTOExists(int id)
        {
            return _context.AnswerDTO.Any(e => e.Id == id);
        }
    }
}
