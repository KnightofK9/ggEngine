using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;
using WebApplication2.DTOs;
using WebApplication2.Data;
using AutoMapper;
using Microsoft.AspNetCore.Identity;
using WebApplication2.Models;

namespace WebApplication2.Controllers.Identity
{
    [Route("api/[controller]")]
    [ApiController]
    public class UsersController : ControllerBase
    {
        private readonly ApplicationDbContext _context;

        //private ILogger logger;
        private readonly UserManager<IdentityUser> _userManager;
        private readonly SignInManager<IdentityUser> _signInManager;

        public UsersController(ApplicationDbContext context)
        {
            _context = context;
        }

        // GET: api/Users
        [HttpGet]
        public async Task<ActionResult<IEnumerable<UserDTO>>> GetUsers()
        {
            var userList = await _context.Users.ToListAsync();
            return userList.Select(user => UserDTO.ToDTO(user)).ToList();
        }

        // GET: api/Users/5
        [HttpGet("{id}")]
        public async Task<ActionResult<UserDTO>> GetUser(string id)
        {
            var user = await _context.Users.FindAsync(id);
            
            if (user == null)
            {
                return NotFound();
            }

            var userDTO = UserDTO.ToDTO(user);
            return userDTO;
        }

        // PUT: api/Users/5
        [HttpPut("{id}")]
        public async Task<IActionResult> PutUser(string id, UserDTO userDTO)
        {
            var user = UserDTO.ToModel(userDTO, _context);

            if (id != user.Id)
            {
                return BadRequest();
            }

            _context.Entry(user).State = EntityState.Modified;

            try
            {
                await _context.SaveChangesAsync();
            }
            catch (DbUpdateConcurrencyException)
            {
                if (!UserDTOExists(id))
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

        // POST: api/Users
        [HttpPost]
        public async Task<ActionResult<UserDTO>> PostUser(UserDTO userDTO)
        {
            var passwordHasher = new PasswordHasher<User>();
            var user = new User()
            {
                Id = userDTO.Id,
                Email = userDTO.Email,
                UserName = userDTO.UserName,
                SecurityStamp = Guid.NewGuid().ToString()
            };
            user.PasswordHash = passwordHasher.HashPassword(user, userDTO.PasswordHash);
            
            _context.Users.Add(user);
            await _context.SaveChangesAsync();

            return CreatedAtAction("GetUser", new { id = user.Id }, userDTO);
        }

        // DELETE: api/Users/5
        [HttpDelete("{id}")]
        public async Task<ActionResult<UserDTO>> DeleteUser(string id)
        {
            var user = await _context.Users.FindAsync(id);
            if (user == null)
            {
                return NotFound();
            }

            _context.Users.Remove(user);
            await _context.SaveChangesAsync();

            var userDTO = UserDTO.ToDTO(user);
            return userDTO;
        }

        private bool UserDTOExists(string id)
        {
            return _context.Users.Any(e => e.Id == id);
        }

        // POST:
        [HttpPost]
        public async Task<IActionResult> Login(UserDTO userDTO)
        {
            //SignInManager<User> signinmanager;// = new SignInManager<User>();
            //var result = await _signManager.PasswordSignInAsync(model.Username,
            //        model.Password, model.RememberMe, false);


            //if (result.Succeeded)
            //    {
            //        if (!string.IsNullOrEmpty(model.ReturnUrl) && Url.IsLocalUrl(model.ReturnUrl))
            //        {
            //            return Redirect(model.ReturnUrl);
            //        }
            //        else
            //        {
            //            return RedirectToAction("Index", "Home");
            //        }
            //    }
            //}
            //ModelState.AddModelError("", "Invalid login attempt");
            //return View(model);

            return null;
        }
    }
}
