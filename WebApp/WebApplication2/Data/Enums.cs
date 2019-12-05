using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace WebApplication2.Data
{
    public class Enums
    {
        public enum AcademicRank
        { 
            Bachelor            = 1 << 0,
            Engineer            = 1 << 1,
            Master              = 1 << 2,
            Doctor              = 1 << 3,
            AssociateProfessor  = 1 << 4,
            Professor           = 1 << 5
        };

        public enum Rate
        {
            Terrible        = 1,
            Poor            = 2,
            Average         = 3,
            Good            = 4,
            Excellent       = 5
        }

        public enum AttendanceStatus
        {
            Absent,
            ExcusedAbsence,
            Present
        }

        public enum DiscusstionStatus
        {
            Opening,
            Closed
        }
    }
}
