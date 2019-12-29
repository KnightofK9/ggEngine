using Microsoft.AspNetCore.Identity;
using Microsoft.AspNetCore.Identity.EntityFrameworkCore;
using Microsoft.EntityFrameworkCore;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using WebApplication2.Models;

namespace WebApplication2.Data
{
    public class ApplicationDbContext : DbContext // : IdentityDbContext<UserModel>
    {
        // Bridge
        public DbSet<CourseLecturer> CourseLecturers { get; set; }
        public DbSet<CourseStudent> CourseStudents { get; set; }
        public DbSet<MessageLecturer> MessageLecturers { get; set; }
        public DbSet<MessageStudent> MessageStudents { get; set; }


        // Course
        public DbSet<Course> Courses { get; set; }
        public DbSet<Lession> Lessions { get; set; }
        public DbSet<Semester> Semesters { get; set; }

        // Identity
        public DbSet<RoleModel> Roles { get; set; }
        public DbSet<User> Users { get; set; }

        // Interaction
        public DbSet<Attendance> Attendances { get; set; }
        public DbSet<Discussion> Discussions { get; set; }
        public DbSet<Document> Documents { get; set; }
        public DbSet<Rate> Rates { get; set; }
        public DbSet<Report> Reports { get; set; }
        
        // Person
        public DbSet<Student> Students { get; set; }
        public DbSet<Lecturer> Lecturers { get; set; }
      
        // QA
        public DbSet<Answer> Answers { get; set; }
        public DbSet<Option> Options { get; set; }
        public DbSet<Question> Questions { get; set; }
        public DbSet<Submission> Submissions { get; set; }
        public DbSet<Test> Tests { get; set; }

        public ApplicationDbContext(DbContextOptions<ApplicationDbContext> options) : base(options) { }

        protected override void OnModelCreating(ModelBuilder builder)
        {
            base.OnModelCreating(builder);
        }
    }
}
