using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;
using WebApplication2.Data;
using WebApplication2.Models;

namespace WebApplication2.Controllers.Interaction
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
        public async Task<ActionResult<IEnumerable<AttendanceModel>>> GetAttendances()
        {
            return await _context.Attendances.ToListAsync();
        }

        // GET: api/Attendances/5
        [HttpGet("{id}")]
        public async Task<ActionResult<AttendanceModel>> GetAttendanceModel(int id)
        {
            var attendanceModel = await _context.Attendances.FindAsync(id);

            if (attendanceModel == null)
            {
                return NotFound();
            }

            return attendanceModel;
        }

        // PUT: api/Attendances/5
        [HttpPut("{id}")]
        public async Task<IActionResult> PutAttendanceModel(int id, AttendanceModel attendanceModel)
        {
            if (id != attendanceModel.Id)
            {
                return BadRequest();
            }

            _context.Entry(attendanceModel).State = EntityState.Modified;

            try
            {
                await _context.SaveChangesAsync();
            }
            catch (DbUpdateConcurrencyException)
            {
                if (!AttendanceModelExists(id))
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
        public async Task<ActionResult<AttendanceModel>> PostAttendanceModel(AttendanceModel attendanceModel)
        {
            _context.Attendances.Add(attendanceModel);
            await _context.SaveChangesAsync();

            return CreatedAtAction("GetAttendanceModel", new { id = attendanceModel.Id }, attendanceModel);
        }

        // DELETE: api/Attendances/5
        [HttpDelete("{id}")]
        public async Task<ActionResult<AttendanceModel>> DeleteAttendanceModel(int id)
        {
            var attendanceModel = await _context.Attendances.FindAsync(id);
            if (attendanceModel == null)
            {
                return NotFound();
            }

            _context.Attendances.Remove(attendanceModel);
            await _context.SaveChangesAsync();

            return attendanceModel;
        }

        private bool AttendanceModelExists(int id)
        {
            return _context.Attendances.Any(e => e.Id == id);
        }
    }
}
