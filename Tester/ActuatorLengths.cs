using System;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using System.Text;

namespace Tester {

    [StructLayout(LayoutKind.Sequential)]
    public readonly struct ActuatorLengths {
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
