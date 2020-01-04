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
    public class CoursesController : ControllerBase
    {
        private readonly ApplicationDbContext _context;

        public CoursesController(ApplicationDbContext context)
        {
            _context = context;
        }

        // GET: api/Courses
        [HttpGet]
        public async Task<ActionResult<IEnumerable<CourseDTO>>> GetCourses()
        {
            var courseList = await _context.Courses.ToListAsync();
            var courseDTOList = new List<CourseDTO>();

            foreach (var course in courseList)
                courseDTOList.Add(CourseDTO.ToDTO(course));

            return courseDTOList;
        }

        // GET: api/Courses/5
        [HttpGet("{id}")]
        public async Task<ActionResult<CourseDTO>> GetCourse(int id)
        {
            var course = await _context.Courses.FindAsync(id);

            if (course == null)
            {
                return NotFound();
            }

            var courseDTO = CourseDTO.ToDTO(course);
            return courseDTO;
        }

        // PUT: api/Courses/5
        [HttpPut("{id}")]
        public async Task<IActionResult> PutCourse(int id, CourseDTO courseDTO)
        {
            var course = CourseDTO.ToModel(courseDTO, _context);

            if (id != course.Id)
            {
                return BadRequest();
            }

            _context.Entry(course).State = EntityState.Modified;

            try
            {
                await _context.SaveChangesAsync();
            }
            catch (DbUpdateConcurrencyException)
            {
                if (!CourseExists(id))
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

        // POST: api/Courses
        [HttpPost]
        public async Task<ActionResult<CourseDTO>> PostCourse(CourseDTO courseDTO)
        {
            var course = CourseDTO.ToModel(courseDTO, _context);

            _context.Courses.Add(course);
            await _context.SaveChangesAsync();

            return CreatedAtAction("GetCourse", new { id = course.Id }, courseDTO);
        }

        // DELETE: api/Courses/5
        [HttpDelete("{id}")]
        public async Task<ActionResult<CourseDTO>> DeleteCourse(int id)
        {
            var course = await _context.Courses.FindAsync(id);
            if (course == null)
            {
                return NotFound();
            }

            _context.Courses.Remove(course);
            await _context.SaveChangesAsync();

            var courseDTO = CourseDTO.ToDTO(course);
            return courseDTO;
        }

        private bool CourseExists(int id)
        {
            return _context.Courses.Any(e => e.Id == id);
        }

        // GET:
        [HttpGet("OfSemester/{semesterId}")]
        public async Task<ActionResult<IEnumerable<CourseDTO>>> GetCoursesOfSemester(int semesterId)
        {
            return _context.Courses.ToList()
                .FindAll(course => course.SemesterId == semesterId)
                .Select(course => CourseDTO.ToDTO(course))
                .ToList();
        }

        // GET:
        [HttpGet("OfStudent/{studentId}")]
        public async Task<ActionResult<IEnumerable<CourseDTO>>> GetCoursesOfStudent(int studentId)
        {
            return _context.CourseStudents.ToList()
                .FindAll(courseStudent => courseStudent.StudentId == studentId)
                .Select(courseStudent => _context.Courses.Find(courseStudent.CourseId))
                .Select(course => CourseDTO.ToDTO(course))
                .ToList();
        }

        // GET:
        [HttpGet("OfLecturer/{lecturerId}")]
        public async Task<ActionResult<IEnumerable<CourseDTO>>> GetCoursesOfLecturer(int lecturerId)
        {
            return _context.CourseLecturers.ToList()
                .FindAll(x => x.LecturerId == lecturerId)
                .Select(courseLecturer => _context.Courses.Find(courseLecturer.CourseId))
                .Select(course => CourseDTO.ToDTO(course))
                .ToList();
        }
    }
}
