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
    public class ReportsController : ControllerBase
    {
        private readonly ApplicationDbContext _context;

        public ReportsController(ApplicationDbContext context)
        {
            _context = context;
        }

        // GET: api/Reports
        [HttpGet]
        public async Task<ActionResult<IEnumerable<ReportDTO>>> GetReportDTO()
        {
            return await _context.ReportDTO.ToListAsync();
        }

        // GET: api/Reports/5
        [HttpGet("{id}")]
        public async Task<ActionResult<ReportDTO>> GetReportDTO(int id)
        {
            var reportDTO = await _context.ReportDTO.FindAsync(id);

            if (reportDTO == null)
            {
                return NotFound();
            }

            return reportDTO;
        }

        // PUT: api/Reports/5
        [HttpPut("{id}")]
        public async Task<IActionResult> PutReportDTO(int id, ReportDTO reportDTO)
        {
            if (id != reportDTO.Id)
            {
                return BadRequest();
            }

            _context.Entry(reportDTO).State = EntityState.Modified;

            try
            {
                await _context.SaveChangesAsync();
            }
            catch (DbUpdateConcurrencyException)
            {
                if (!ReportDTOExists(id))
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

        // POST: api/Reports
        [HttpPost]
        public async Task<ActionResult<ReportDTO>> PostReportDTO(ReportDTO reportDTO)
        {
            _context.ReportDTO.Add(reportDTO);
            await _context.SaveChangesAsync();

            return CreatedAtAction("GetReportDTO", new { id = reportDTO.Id }, reportDTO);
        }

        // DELETE: api/Reports/5
        [HttpDelete("{id}")]
        public async Task<ActionResult<ReportDTO>> DeleteReportDTO(int id)
        {
            var reportDTO = await _context.ReportDTO.FindAsync(id);
            if (reportDTO == null)
            {
                return NotFound();
            }

            _context.ReportDTO.Remove(reportDTO);
            await _context.SaveChangesAsync();

            return reportDTO;
        }

        private bool ReportDTOExists(int id)
        {
            return _context.ReportDTO.Any(e => e.Id == id);
        }
    }
}
