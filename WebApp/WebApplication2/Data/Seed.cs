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

            if (!applicationContext.Users.Any())
            {
                var user = new UserModel
                {
                    Email = "email_user@com",
                    SecurityStamp = Guid.NewGuid().ToString(),
                    UserName = "user_admin"
                };

                var password = new PasswordHasher<UserModel>();
                var hashed = password.HashPassword(user, "Password_123");
                user.PasswordHash = hashed;

                //var userManager = new UserManager<UserModel>(new UserStore<UserModel>(applicationContext));
                //var userManager = serviceProvider.GetRequiredService<UserManager<UserModel>>();
                var userStore = new UserStore<UserModel>(applicationContext);
                userStore.CreateAsync(user);
            }

            //// Lecturer
            //if (!applicationContext.Lecturers.Any())
            //{
            //    applicationContext.Lecturers.Add(new LecturerModel
            //    {
            //        LectureCode = "LT_001",
            //        FirstName = "John",
            //        LastName = "Quick"
            //    });
            //}

            //// Student
            //if (!applicationContext.Students.Any())
            //{
            //    applicationContext.Students.Add(new StudentModel
            //    {
            //        Id = 1,
            //        StudentCode = "ST_001"
            //        //FirstName = "Harry",
            //        //LastName = "Poster"
            //    });
            //}

            applicationContext.SaveChanges();
            applicationContext.SaveChangesAsync();
        }
    }
}
