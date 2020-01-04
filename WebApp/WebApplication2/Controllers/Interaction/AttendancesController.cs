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
    public class AttendancesController : ControllerBase
    {
        private readonly ApplicationDbContext _context;

        public AttendancesController(ApplicationDbContext context)
        {
            _context = context;
        }

        // GET: api/Attendances
        [HttpGet]
        public async Task<ActionResult<IEnumerable<AttendanceDTO>>> GetAttendances()
        {
            var attendanceList = await _context.Attendances.ToListAsync();
            var attendanceDTOList = new List<AttendanceDTO>();

            foreach (var attendance in attendanceList)
                attendanceDTOList.Add(AttendanceDTO.ToDTO(attendance));

            return attendanceDTOList;
        }

        // GET: api/Attendances/5
        [HttpGet("{id}")]
        public async Task<ActionResult<AttendanceDTO>> GetAttendance(int id)
        {
            var attendance = await _context.Attendances.FindAsync(id);

            if (attendance == null)
            {
                return NotFound();
            }

            var attendanceDTO = AttendanceDTO.ToDTO(attendance);
            return attendanceDTO;
        }

        // PUT: api/Attendances/5
        [HttpPut("{id}")]
        public async Task<IActionResult> PutAttendance(int id, AttendanceDTO attendanceDTO)
        {
            var attendance = AttendanceDTO.ToModel(attendanceDTO, _context);

            if (id != attendance.Id)
            {
                return BadRequest();
            }

            _context.Entry(attendance).State = EntityState.Modified;

            try
            {
                await _context.SaveChangesAsync();
            }
            catch (DbUpdateConcurrencyException)
            {
                if (!AttendanceExists(id))
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
        public async Task<ActionResult<AttendanceDTO>> PostAttendance(AttendanceDTO attendanceDTO)
        {
            var attendance = AttendanceDTO.ToModel(attendanceDTO, _context);

            _context.Attendances.Add(attendance);
            await _context.SaveChangesAsync();

            return CreatedAtAction("GetAttendance", new { id = attendance.Id }, attendanceDTO);
        }

        // DELETE: api/Attendances/5
        [HttpDelete("{id}")]
        public async Task<ActionResult<AttendanceDTO>> DeleteAttendance(int id)
        {
            var attendance = await _context.Attendances.FindAsync(id);
            if (attendance == null)
            {
                return NotFound();
            }

            _context.Attendances.Remove(attendance);
            await _context.SaveChangesAsync();

            var attendanceDTO = AttendanceDTO.ToDTO(attendance);
            return attendanceDTO;
        }

        private bool AttendanceExists(int id)
        {
            return _context.Attendances.Any(e => e.Id == id);
        }
    }
}
