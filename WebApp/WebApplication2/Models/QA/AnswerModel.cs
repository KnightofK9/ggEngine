﻿using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Threading.Tasks;

namespace WebApplication2.Models
{
    public class AnswerModel
    {
        [Key]
        public int Id { get; set; }

        public int QuestionId { get; set; }

        public int SelectionId { get; set; }
    }
}
