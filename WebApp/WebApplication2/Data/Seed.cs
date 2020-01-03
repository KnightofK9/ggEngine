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
        public static void Initialize(IServiceProvider serviceProvider)
        {
            var applicationContext = serviceProvider.GetRequiredService<ApplicationDbContext>();

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


            applicationContext.SaveChangesAsync();
            applicationContext.SaveChangesAsync();
        }
    }
}
