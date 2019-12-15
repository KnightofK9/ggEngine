using Microsoft.AspNetCore.Authorization;
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
        //public static bool CreatRoleAsync(IServiceProvider serviceProvider, string roleName)
        //{
        //    var RoleManager = serviceProvider.GetRequiredService<RoleManager<IdentityRole>>();
        //    var UserManager = serviceProvider.GetRequiredService<UserManager<IdentityUser>>();

        //    var roleExist = RoleManager.RoleExistsAsync(roleName);
        //    if (roleExist.Result)
        //    {
        //        var result = RoleManager.CreateAsync(new IdentityRole(roleName));
        //        return result.Result.Succeeded;
        //    }
        //    else
        //        return false;
        //}

        //public static void AsignUserRoleAsync(IServiceProvider serviceProvider, string userName, string roleName)​
        //{
        //serviceProvider.
        //            var _user = UserManager.F
        //            (Configuration.GetSection("UserSettings")["UserEmail"]);
        //​
        //            if (_user == null)
        //                {
        //                    var createPowerUser = await UserManager.CreateAsync(poweruser, UserPassword);
        //                    if (createPowerUser.Succeeded)
        //                    {
        //                        //here we tie the new user to the "Admin" role 
        //                        await UserManager.AddToRoleAsync(poweruser, "Admin");
        //​
        //                    }
        //                }
        //            }
        //}
        

        public static void Initialize(IServiceProvider serviceProvider)
        {
            var applicationContext = serviceProvider.GetRequiredService<ApplicationDbContext>();

            // Users

            var passwordHasher = new PasswordHasher<UserModel>();
            var userStore = new UserStore<UserModel>(applicationContext);
            
            if (!applicationContext.Users.Any())
            {
                var adminUser = new UserModel
                {
                    Email = "admin@com",
                    UserName = "admin",
                };
                adminUser.PasswordHash = passwordHasher.HashPassword(adminUser, "pwadmin");
                userStore.CreateAsync(adminUser);
            }

            // Lecturer
            //if (!applicationContext.Lecturers.Any())
            //{
            //    var lecturerUser = new IdentityUser
            //    {
            //        Email = "lt001@com",
            //        UserName = "lt001"
            //    };
            //    lecturerUser.PasswordHash = passwordHasher.HashPassword(lecturerUser, "pwlt001");
            //    userStore.CreateAsync(lecturerUser);

            //    applicationContext.Lecturers.Add(new LecturerModel
            //    {
            //        LecturerCode = "LT001",
            //        FirstName = "Join",
            //        LastName = "Quick",
            //        User = lecturerUser
            //    });
            //}

            //// Student
            //if (!applicationContext.Students.Any())
            //{
            //    var studentUser = new IdentityUser
            //    {
            //        Email = "st001@com",
            //        UserName = "st001"
            //    };
            //    studentUser.PasswordHash = passwordHasher.HashPassword(studentUser, "pwst001");
            //    userStore.CreateAsync(studentUser);

            //    applicationContext.Students.Add(new StudentModel
            //    {
            //        StudentCode = "ST001",
            //        FirstName = "Harry",
            //        LastName = "Poster",                    
            //        User = studentUser
            //    });
            //}

            applicationContext.SaveChangesAsync();
            applicationContext.SaveChangesAsync();
        }
    }
}
