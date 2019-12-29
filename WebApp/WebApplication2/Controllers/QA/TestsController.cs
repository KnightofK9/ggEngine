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
    public class TestsController : ControllerBase
    {
        private readonly ApplicationDbContext _context;

        public TestsController(ApplicationDbContext context)
        {
            _context = context;
        }

        // GET: api/Tests
        [HttpGet]
        public async Task<ActionResult<IEnumerable<TestDTO>>> GetTestDTO()
        {
            return await _context.TestDTO.ToListAsync();
        }

        // GET: api/Tests/5
        [HttpGet("{id}")]
        public async Task<ActionResult<TestDTO>> GetTestDTO(int id)
        {
            var testDTO = await _context.TestDTO.FindAsync(id);

            if (testDTO == null)
            {
                return NotFound();
            }

            return testDTO;
        }

        // PUT: api/Tests/5
        [HttpPut("{id}")]
        public async Task<IActionResult> PutTestDTO(int id, TestDTO testDTO)
        {
            if (id != testDTO.Id)
            {
                return BadRequest();
            }

            _context.Entry(testDTO).State = EntityState.Modified;

            try
            {
                await _context.SaveChangesAsync();
            }
            catch (DbUpdateConcurrencyException)
            {
                if (!TestDTOExists(id))
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

        // POST: api/Tests
        [HttpPost]
        public async Task<ActionResult<TestDTO>> PostTestDTO(TestDTO testDTO)
        {
            _context.TestDTO.Add(testDTO);
            await _context.SaveChangesAsync();

            return CreatedAtAction("GetTestDTO", new { id = testDTO.Id }, testDTO);
        }

        // DELETE: api/Tests/5
        [HttpDelete("{id}")]
        public async Task<ActionResult<TestDTO>> DeleteTestDTO(int id)
        {
            var testDTO = await _context.TestDTO.FindAsync(id);
            if (testDTO == null)
            {
                return NotFound();
            }

            _context.TestDTO.Remove(testDTO);
            await _context.SaveChangesAsync();

            return testDTO;
        }

        private bool TestDTOExists(int id)
        {
            return _context.TestDTO.Any(e => e.Id == id);
        }
    }
}
