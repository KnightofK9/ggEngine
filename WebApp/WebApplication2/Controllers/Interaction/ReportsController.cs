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
    public class ReportsController : ControllerBase
    {
        private readonly ApplicationDbContext _context;

        public ReportsController(ApplicationDbContext context)
        {
            _context = context;
        }

        // GET: api/Reports
        [HttpGet]
        public async Task<ActionResult<IEnumerable<ReportModel>>> GetReports()
        {
            return await _context.Reports.ToListAsync();
        }

        // GET: api/Reports/5
        [HttpGet("{id}")]
        public async Task<ActionResult<ReportModel>> GetReportModel(int id)
        {
            var reportModel = await _context.Reports.FindAsync(id);

            if (reportModel == null)
            {
                return NotFound();
            }

            return reportModel;
        }

        // PUT: api/Reports/5
        [HttpPut("{id}")]
        public async Task<IActionResult> PutReportModel(int id, ReportModel reportModel)
        {
            if (id != reportModel.Id)
            {
                return BadRequest();
            }

            _context.Entry(reportModel).State = EntityState.Modified;

            try
            {
                await _context.SaveChangesAsync();
            }
            catch (DbUpdateConcurrencyException)
            {
                if (!ReportModelExists(id))
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
        public async Task<ActionResult<ReportModel>> PostReportModel(ReportModel reportModel)
        {
            _context.Reports.Add(reportModel);
            await _context.SaveChangesAsync();

            return CreatedAtAction("GetReportModel", new { id = reportModel.Id }, reportModel);
        }

        // DELETE: api/Reports/5
        [HttpDelete("{id}")]
        public async Task<ActionResult<ReportModel>> DeleteReportModel(int id)
        {
            var reportModel = await _context.Reports.FindAsync(id);
            if (reportModel == null)
            {
                return NotFound();
            }

            _context.Reports.Remove(reportModel);
            await _context.SaveChangesAsync();

            return reportModel;
        }

        private bool ReportModelExists(int id)
        {
            return _context.Reports.Any(e => e.Id == id);
        }
    }
}
