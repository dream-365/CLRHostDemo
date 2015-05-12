using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ManangedLib
{
    public class TestClass
    {

        public static int OnStart(string arg)
        {
            SayHiTo(arg);

            return 123;
        }

        public static void SayHiTo(string to)
        {
            Console.WriteLine("Hi! " + to);
        }
    }
}
