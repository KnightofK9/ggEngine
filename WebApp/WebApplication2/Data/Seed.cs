using Microsoft.AspNetCore.Identity;
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
            var context = new ApplicationDbContext(serviceProvider.GetRequiredService<DbContextOptions<ApplicationDbContext>>());
            var userManager = serviceProvider.GetRequiredService<UserManager<UserModel>>();

            context.Database.EnsureCreated();
            if (!context.Users.Any())
            {
                UserModel user = new UserModel()
                {
                    Email = "email_user@com",
                    SecurityStamp = Guid.NewGuid().ToString(),
                    UserName = "user_admin",                    
                };
                //context.Users.Add(user);
                //context.SaveChanges();
                userManager.CreateAsync(user, "Password_abc123");
            }
        }
    }
}
