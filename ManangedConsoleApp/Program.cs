using System;
using System.Collections.Generic;
using System.Configuration;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ManangedConsoleApp
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("key1: " + ConfigurationManager.AppSettings.Get("key1"));
        }
    }
}
