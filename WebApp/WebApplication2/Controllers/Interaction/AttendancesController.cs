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
    public class AttendancesController : ControllerBase
    {
        private readonly ApplicationDbContext _context;

        public AttendancesController(ApplicationDbContext context)
        {
            _context = context;
        }

        // GET: api/Attendances
        [HttpGet]
        public async Task<ActionResult<IEnumerable<AttendanceDTO>>> GetAttendanceDTO()
        {
            return await _context.AttendanceDTO.ToListAsync();
        }

        // GET: api/Attendances/5
        [HttpGet("{id}")]
        public async Task<ActionResult<AttendanceDTO>> GetAttendanceDTO(int id)
        {
            var attendanceDTO = await _context.AttendanceDTO.FindAsync(id);

            if (attendanceDTO == null)
            {
                return NotFound();
            }

            return attendanceDTO;
        }

        // PUT: api/Attendances/5
        [HttpPut("{id}")]
        public async Task<IActionResult> PutAttendanceDTO(int id, AttendanceDTO attendanceDTO)
        {
            if (id != attendanceDTO.Id)
            {
                return BadRequest();
            }

            _context.Entry(attendanceDTO).State = EntityState.Modified;

            try
            {
                await _context.SaveChangesAsync();
            }
            catch (DbUpdateConcurrencyException)
            {
                if (!AttendanceDTOExists(id))
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

        // POST: api/Attendances
        [HttpPost]
        public async Task<ActionResult<AttendanceDTO>> PostAttendanceDTO(AttendanceDTO attendanceDTO)
        {
            _context.AttendanceDTO.Add(attendanceDTO);
            await _context.SaveChangesAsync();

            return CreatedAtAction("GetAttendanceDTO", new { id = attendanceDTO.Id }, attendanceDTO);
        }

        // DELETE: api/Attendances/5
        [HttpDelete("{id}")]
        public async Task<ActionResult<AttendanceDTO>> DeleteAttendanceDTO(int id)
        {
            var attendanceDTO = await _context.AttendanceDTO.FindAsync(id);
            if (attendanceDTO == null)
            {
                return NotFound();
            }

            _context.AttendanceDTO.Remove(attendanceDTO);
            await _context.SaveChangesAsync();

            return attendanceDTO;
        }

        private bool AttendanceDTOExists(int id)
        {
            return _context.AttendanceDTO.Any(e => e.Id == id);
        }
    }
}
