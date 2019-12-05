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
    public class ApplicationDbContext : IdentityDbContext<IdentityUser>
    {
        public DbSet<StudentModel> Students { get; set; }
        public DbSet<LecturerModel> Lecturers { get; set; }

        public DbSet<ClassModel> Classes { get; set; }
        public DbSet<LessionModel> Lessions { get; set; }
        public DbSet<SemesterModel> Semesters { get; set; }

        public DbSet<AttendanceModel> Attendances { get; set; }
        public DbSet<DiscussionModel> Discussions { get; set; }
        public DbSet<DocumentModel> Documents { get; set; }
        public DbSet<LecturerMessageModel> LecturerMessages { get; set; }
        public DbSet<StudentMessageModel> StudentMessages { get; set; }
        public DbSet<RateModel> Rates { get; set; }
        public DbSet<ReportModel> Reports { get; set; }

        public DbSet<AnswerModel> Answers { get; set; }
        public DbSet<OptionModel> Options { get; set; }
        public DbSet<QuestionModel> Questions { get; set; }
        public DbSet<SubmissionModel> Submissions { get; set; }
        public DbSet<TestModel> Tests { get; set; }

        public ApplicationDbContext(DbContextOptions<ApplicationDbContext> options) : base(options) { }

        protected override void OnModelCreating(ModelBuilder builder)
        {
            base.OnModelCreating(builder);
        }
    }
}
