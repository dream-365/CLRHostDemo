using System;
using System.Collections.Generic;
using System.Data.Common;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Configuration;

namespace ManangedLib
{
    public class TestClass
    {

        public static int OnStart(string arg)
        {
            SayHiTo(arg);

            PrintConfigSettings();

            return 123;
        }

        public static void SayHiTo(string to)
        {
            Console.WriteLine("Hi! " + to);
        }

        public static void PrintConfigSettings()
        {
            string value = ConfigurationManager.AppSettings.Get("key1");

            Console.WriteLine("key1: " + value);

            var table = DbProviderFactories.GetFactoryClasses();

            Console.WriteLine("Classes Count: " + table.Rows.Count);           
        }
    }
}
