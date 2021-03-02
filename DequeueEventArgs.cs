using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Simvars
{
    class DequeueEventArgs : EventArgs
    {
        public Hashtable t;
        public DequeueEventArgs(Hashtable t)
        {
            this.t = t;
        }
    }
}
