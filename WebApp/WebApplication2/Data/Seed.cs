using Microsoft.AspNetCore.Identity;
using Microsoft.AspNetCore.Identity.EntityFrameworkCore;
using Microsoft.EntityFrameworkCore;
using Microsoft.Extensions.DependencyInjection;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using WebApplication2.Models;

namespace WebApplication2.Data
{
    public class Seed
    {
        public static void Initialize(IServiceProvider serviceProvider)
        {
            var applicationContext = serviceProvider.GetRequiredService<ApplicationDbContext>();

            var passwordHasher = new PasswordHasher<UserModel>();
            var userStore = new UserStore<UserModel>(applicationContext);

            if (!applicationContext.Users.Any())
            {
                var adminUser = new UserModel
                {
                    Email = "admin@com",
                    SecurityStamp = Guid.NewGuid().ToString(),
                    UserName = "admin"
                };
                adminUser.PasswordHash = passwordHasher.HashPassword(adminUser, "pwadmin");
                userStore.CreateAsync(adminUser);
            }

            // Lecturer
            if (!applicationContext.Lecturers.Any())
            {
                var lecturerUser = new UserModel
                {
                    Email = "lt001@com",
                    SecurityStamp = Guid.NewGuid().ToString(),
                    UserName = "lt001"
                };
                lecturerUser.PasswordHash = passwordHasher.HashPassword(lecturerUser, "pwlt001");
                userStore.CreateAsync(lecturerUser);

                applicationContext.Lecturers.Add(new LecturerModel
                {
                    LecturerCode = "LT001",
                    FirstName = "Join",
                    LastName = "Quick",
                    User = lecturerUser
                });
            }

            // Student
            if (!applicationContext.Students.Any())
            {
                var studentUser = new UserModel
                {
                    Email = "st001@com",
                    SecurityStamp = Guid.NewGuid().ToString(),
                    UserName = "st001"
                };
                studentUser.PasswordHash = passwordHasher.HashPassword(studentUser, "pwst001");
                userStore.CreateAsync(studentUser);

                applicationContext.Students.Add(new StudentModel
                {
                    StudentCode = "ST001",
                    FirstName = "Harry",
                    LastName = "Poster",
                    User = studentUser
                });
            }

            applicationContext.SaveChanges();
            applicationContext.SaveChangesAsync();
        }
    }
}
