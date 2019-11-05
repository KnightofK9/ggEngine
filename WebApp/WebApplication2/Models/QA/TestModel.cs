using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Runtime.Serialization;
using System.Threading.Tasks;

namespace WebApplication2.Models
{
    [KnownType(typeof(TestModel2)), KnownType(typeof(TestModel3))]
    public class TestModel1
    {
        [Key]
        public int Id { get; set; }
        public string Name { get; set; }
    }

    public class TestModel2 : TestModel1
    {
        public string Type {get; set; }
    }

    public class TestModel3 : TestModel1
    {
        public string Value { get; set; }
    }
}
