using Microsoft.AspNetCore.DataProtection.KeyManagement;
using Microsoft.AspNetCore.Identity;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using WebApplication2.Data;
using WebApplication2.Models;

namespace WebApplication2.DTOs
{
    public class UserDTO
    {
        public string Id { get; set; }

        public string UserName { get; set; }

        public string Email { get; set; }

        public string PasswordHash { get; set; }

        public static User ToModel(UserDTO userDTO, ApplicationDbContext context)
        {
            var passwordHasher = new PasswordHasher<User>();
            var user = new User()
            {
                Id = userDTO.Id,
                Email = userDTO.Email,
                UserName = userDTO.UserName,
                SecurityStamp = Guid.NewGuid().ToString("D")
            };
            user.PasswordHash = passwordHasher.HashPassword(user, userDTO.PasswordHash);
            return user;
        }

        public static UserDTO ToDTO(User user)
        {
            return new UserDTO()
            {
                Id = user.Id,
                Email = user.Email,
                UserName = user.UserName,
                PasswordHash = user.PasswordHash
            };
        }
    }
}
