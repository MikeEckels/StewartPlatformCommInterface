using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;

namespace PlatformLibrary {

    [StructLayout(LayoutKind.Sequential)]
    public readonly struct ActuatorLengths
    {
        public readonly double U;
        public readonly double V;
        public readonly double W;
        public readonly double X;
        public readonly double Y;
        public readonly double Z;
        //private byte _constraintSuccess;
        //public bool constraintSuccess
        //{
        //    get
        //    {
        //        return _constraintSuccess != 0;
        //    }
        //}
    };
}
