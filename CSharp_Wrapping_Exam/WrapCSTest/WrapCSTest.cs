using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace WrapCSTest
{
    class WrapCSTest
    {
        static void Main(string[] args)
        {
            WrappedClass.CWrappedClass obj = new WrappedClass.CWrappedClass();
            Console.WriteLine(obj.CallGetSum());
            Console.Read();
        }
    }
}
