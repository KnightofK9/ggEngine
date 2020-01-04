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
    public class TestsController : ControllerBase
    {
        private readonly ApplicationDbContext _context;

        public TestsController(ApplicationDbContext context)
        {
            _context = context;
        }

        // GET: api/Tests
        [HttpGet]
        public async Task<ActionResult<IEnumerable<TestDTO>>> GetTests()
        {
            var testList = await _context.Tests.ToListAsync();
            var testDTOList = new List<TestDTO>();

            foreach (var test in testList)
                testDTOList.Add(TestDTO.ToDTO(test));

            return testDTOList;
        }

        // GET: api/Tests/5
        [HttpGet("{id}")]
        public async Task<ActionResult<TestDTO>> GetTest(int id)
        {
            var test = await _context.Tests.FindAsync(id);

            if (test == null)
            {
                return NotFound();
            }

            var testDTO = TestDTO.ToDTO(test);
            return testDTO;
        }

        // PUT: api/Tests/5
        [HttpPut("{id}")]
        public async Task<IActionResult> PutTest(int id, TestDTO testDTO)
        {
            var test = TestDTO.ToModel(testDTO, _context);

            if (id != test.Id)
            {
                return BadRequest();
            }

            _context.Entry(test).State = EntityState.Modified;

            try
            {
                await _context.SaveChangesAsync();
            }
            catch (DbUpdateConcurrencyException)
            {
                if (!TestExists(id))
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
        public async Task<ActionResult<TestDTO>> PostTest(TestDTO testDTO)
        {
            var test = TestDTO.ToModel(testDTO, _context);

            _context.Tests.Add(test);
            await _context.SaveChangesAsync();

            return CreatedAtAction("GetTest", new { id = test.Id }, testDTO);
        }

        // DELETE: api/Tests/5
        [HttpDelete("{id}")]
        public async Task<ActionResult<TestDTO>> DeleteTest(int id)
        {
            var test = await _context.Tests.FindAsync(id);
            if (test == null)
            {
                return NotFound();
            }

            _context.Tests.Remove(test);
            await _context.SaveChangesAsync();

            var testDTO = TestDTO.ToDTO(test);
            return testDTO;
        }

        private bool TestExists(int id)
        {
            return _context.Tests.Any(e => e.Id == id);
        }

        // GET:
        [HttpGet("OfLession/{lessionId}")]
        public async Task<ActionResult<IEnumerable<TestDTO>>> GetTestsOfLession(int lessionId)
        {
            return _context.Tests.ToList()
                .FindAll(test => test.LessionId == lessionId)
                .Select(test => TestDTO.ToDTO(test))
                .ToList();
        }
    }
}
