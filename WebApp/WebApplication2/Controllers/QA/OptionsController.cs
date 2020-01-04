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
    public class OptionsController : ControllerBase
    {
        private readonly ApplicationDbContext _context;

        public OptionsController(ApplicationDbContext context)
        {
            _context = context;
        }

        // GET: api/Options
        [HttpGet]
        public async Task<ActionResult<IEnumerable<OptionDTO>>> GetOptions()
        {
            var optionList = await _context.Options.ToListAsync();
            var optionDTOList = new List<OptionDTO>();

            foreach (var option in optionList)
                optionDTOList.Add(OptionDTO.ToDTO(option));

            return optionDTOList;
        }

        // GET: api/Options/5
        [HttpGet("{id}")]
        public async Task<ActionResult<OptionDTO>> GetOption(int id)
        {
            var option = await _context.Options.FindAsync(id);

            if (option == null)
            {
                return NotFound();
            }

            var optionDTO = OptionDTO.ToDTO(option);
            return optionDTO;
        }

        // PUT: api/Options/5
        [HttpPut("{id}")]
        public async Task<IActionResult> PutOption(int id, OptionDTO optionDTO)
        {
            var option = OptionDTO.ToModel(optionDTO, _context);

            if (id != option.Id)
            {
                return BadRequest();
            }

            _context.Entry(option).State = EntityState.Modified;

            try
            {
                await _context.SaveChangesAsync();
            }
            catch (DbUpdateConcurrencyException)
            {
                if (!OptionExists(id))
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

        // POST: api/Options
        [HttpPost]
        public async Task<ActionResult<OptionDTO>> PostOption(OptionDTO optionDTO)
        {
            var option = OptionDTO.ToModel(optionDTO, _context);

            _context.Options.Add(option);
            await _context.SaveChangesAsync();

            return CreatedAtAction("GetOption", new { id = option.Id }, optionDTO);
        }

        // DELETE: api/Options/5
        [HttpDelete("{id}")]
        public async Task<ActionResult<OptionDTO>> DeleteOption(int id)
        {
            var option = await _context.Options.FindAsync(id);
            if (option == null)
            {
                return NotFound();
            }

            _context.Options.Remove(option);
            await _context.SaveChangesAsync();

            var optionDTO = OptionDTO.ToDTO(option);
            return optionDTO;
        }

        private bool OptionExists(int id)
        {
            return _context.Options.Any(e => e.Id == id);
        }
    }
}
