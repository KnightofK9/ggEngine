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
    public class CourseStudentsController : ControllerBase
    {
        private readonly ApplicationDbContext _context;

        public CourseStudentsController(ApplicationDbContext context)
        {
            _context = context;
        }

        // GET: api/CourseStudents
        [HttpGet]
        public async Task<ActionResult<IEnumerable<CourseStudentDTO>>> GetCourseStudents()
        {
            var courseStudentList = await _context.CourseStudents.ToListAsync();
            var courseStudentDTOList = new List<CourseStudentDTO>();

            foreach (var courseStudent in courseStudentList)
                courseStudentDTOList.Add(CourseStudentDTO.ToDTO(courseStudent));

            return courseStudentDTOList;
        }

        // GET: api/CourseStudents/5
        [HttpGet("{id}")]
        public async Task<ActionResult<CourseStudentDTO>> GetCourseStudent(int id)
        {
            var courseStudent = await _context.CourseStudents.FindAsync(id);

            if (courseStudent == null)
            {
                return NotFound();
            }

            var courseStudentDTO = CourseStudentDTO.ToDTO(courseStudent);
            return courseStudentDTO;
        }

        // PUT: api/CourseStudents/5
        [HttpPut("{id}")]
        public async Task<IActionResult> PutCourseStudent(int id, CourseStudentDTO courseStudentDTO)
        {
            var courseStudent = CourseStudentDTO.ToModel(courseStudentDTO, _context);

            if (id != courseStudent.Id)
            {
                return BadRequest();
            }

            _context.Entry(courseStudent).State = EntityState.Modified;

            try
            {
                await _context.SaveChangesAsync();
            }
            catch (DbUpdateConcurrencyException)
            {
                if (!CourseStudentExists(id))
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

        // POST: api/CourseStudents
        [HttpPost]
        public async Task<ActionResult<CourseStudentDTO>> PostCourseStudent(CourseStudentDTO courseStudentDTO)
        {
            var courseStudent = CourseStudentDTO.ToModel(courseStudentDTO, _context);

            _context.CourseStudents.Add(courseStudent);
            await _context.SaveChangesAsync();

            return CreatedAtAction("GetCourseStudent", new { id = courseStudent.Id }, courseStudentDTO);
        }

        // DELETE: api/CourseStudents/5
        [HttpDelete("{id}")]
        public async Task<ActionResult<CourseStudentDTO>> DeleteCourseStudent(int id)
        {
            var courseStudent = await _context.CourseStudents.FindAsync(id);
            if (courseStudent == null)
            {
                return NotFound();
            }

            _context.CourseStudents.Remove(courseStudent);
            await _context.SaveChangesAsync();

            var courseStudentDTO = CourseStudentDTO.ToDTO(courseStudent);
            return courseStudentDTO;
        }

        private bool CourseStudentExists(int id)
        {
            return _context.CourseStudents.Any(e => e.Id == id);
        }
    }
}
