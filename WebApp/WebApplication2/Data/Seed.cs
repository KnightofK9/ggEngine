using Microsoft.AspNetCore.Authorization;
using Microsoft.AspNetCore.Identity;
using Microsoft.AspNetCore.Identity.EntityFrameworkCore;
using Microsoft.EntityFrameworkCore;
using Microsoft.Extensions.DependencyInjection;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using WebApplication2.DTOs;
using WebApplication2.Models;

namespace WebApplication2.Data
{
    public class Seed
    {
        public static void Initialize(IServiceProvider serviceProvider)
        {
            var applicationContext = serviceProvider.GetRequiredService<ApplicationDbContext>();

            // Semesters
            if (!applicationContext.Semesters.Any())
            {
                applicationContext.Semesters.AddRange(new List<Semester>()
                {
                    new Semester()
                    {
                        Name = "HK1 2020"
                    }
                });
                applicationContext.SaveChanges();
            }

            // Courses
            if (!applicationContext.Courses.Any())
            {
                applicationContext.Courses.AddRange(new List<Course>()
                {
                    new Course()
                    {
                        Code = "IT001",
                        Name = "Nhap mon lap trinh",
                        StartDate = DateTime.Parse("2020/01/01"),
                        EndDate = DateTime.Parse("2020/06/01"),
                        SemesterId = applicationContext.Semesters.First().Id
                    },
                    new Course()
                    {
                        Code = "IT002",
                        Name = "Lap trinh huong doi tuong",
                        StartDate = DateTime.Parse("2020/01/01"),
                        EndDate = DateTime.Parse("2020/06/01"),
                        SemesterId = applicationContext.Semesters.First().Id
                    }
                });
                applicationContext.SaveChanges();
            }

            // Users
            if (!applicationContext.Users.Any())
            {
                applicationContext.Users.AddRange(new List<User>()
                {
                    UserDTO.ToModel(new UserDTO()
                    {
                        UserName = "admin",
                        PasswordHash = "admin123"
                    }, applicationContext),
                    UserDTO.ToModel(new UserDTO()
                    {
                        UserName = "lecturer_25",
                        PasswordHash = "1234"
                    }, applicationContext),
                    UserDTO.ToModel(new UserDTO()
                    {
                        UserName = "student_12",
                        PasswordHash = "abcd"
                    }, applicationContext)
                });
                applicationContext.SaveChanges();
            }

            // Lecturers
            if (!applicationContext.Lecturers.Any())
            {
                applicationContext.Lecturers.AddRange(new List<Lecturer>()
                {
                    new Lecturer()
                    {
                        Code = "LT25",
                        AcademicRank = Enums.AcademicRank.Master,
                        IsMale = true,
                        FirstName = "Tran",
                        LastName = "Dung"                       
                    }
                });
                applicationContext.SaveChanges();
            }

            // Student
            if (!applicationContext.Students.Any())
            {
                applicationContext.Students.AddRange(new List<Student>()
                {
                    new Student()
                    {
                        Code = "ST12",
                        NickName = "st12",
                        Anonymous = false,
                        IsMale = true,
                        FirstName = "Nguyen",
                        LastName = "Khanh"
                    }
                });
                applicationContext.SaveChanges();
            }

            // Roles
            //var roleStore = new RoleStore<RoleModel>(applicationContext);
            //if (!roleStore.Roles.Any())
            //{
            //    var adminRole = new RoleModel
            //    {
            //        Name = "Administrator"
            //    };
            //    roleStore.CreateAsync(adminRole);
            //}

            // Users
            //var passwordHasher = new PasswordHasher<User>();
            //var userStore = new UserStore<User>(applicationContext);            
            //if (!userStore.Users.Any())
            //{
            //    var adminUser = new User
            //    {
            //        Email = "admin@com",
            //        UserName = "admin",
            //    };
            //    adminUser.PasswordHash = passwordHasher.HashPassword(adminUser, "pwadmin");
            //    userStore.CreateAsync(adminUser);

            //}

            //var user = userStore.FindByNameAsync("admin").Result;
            //userStore.AddToRoleAsync(user, "Administrator");


            applicationContext.SaveChanges();
        }
    }
}
