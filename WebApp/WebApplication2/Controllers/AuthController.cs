using System;
using System.Collections.Generic;
using System.IdentityModel.Tokens.Jwt;
using System.Linq;
using System.Security.Claims;
using System.Text;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Authorization;
using Microsoft.AspNetCore.Identity;
using Microsoft.AspNetCore.Mvc;
using Microsoft.IdentityModel.Tokens;
using WebApplication2.Data;
using WebApplication2.Models;
using Microsoft.Extensions.Configuration;

namespace WebApplication2.Controllers
{
    [Route("api/[controller]")]
    [ApiController]
    [AllowAnonymous]
    public class AuthController : Controller
    {
        private UserManager<UserModel> _userManager;
        public IConfiguration Configuration { get; set; }

        public AuthController(IConfiguration configuration, UserManager<UserModel> userManager)
        {
            Configuration = configuration;
            _userManager = userManager;
        }
        
        [HttpPost]
        [Route("login")]
        public async Task<IActionResult> Login([FromBody] LoginDTO dto)
        {
            var user = await _userManager.FindByNameAsync(dto.UserName);
            if (user != null && await _userManager.CheckPasswordAsync(user, dto.Password))
            {
                var claims = new[]
                {
                    new Claim(JwtRegisteredClaimNames.Sub, user.UserName),
                    new Claim(JwtRegisteredClaimNames.Jti, Guid.NewGuid().ToString())
                };

                var signingKey = new SymmetricSecurityKey(Encoding.UTF8.GetBytes(Configuration["SecurityKey"]));

                var token = new JwtSecurityToken(
                    issuer: "http://abc.com",
                    audience: "http://abc.com",
                    expires: DateTime.UtcNow.AddHours(1),
                    claims: claims,
                    signingCredentials: new SigningCredentials(signingKey, SecurityAlgorithms.HmacSha256)
                    );

                return Ok(new
                {
                    token = new JwtSecurityTokenHandler().WriteToken(token),
                    expiration = token.ValidTo
                });
            }

            return Unauthorized();
        }
    }
}