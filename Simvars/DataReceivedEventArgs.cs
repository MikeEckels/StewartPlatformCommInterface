using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SimWatcher
{
    class DataReceivedEventArgs : EventArgs
    {
        public DataReceivedEventArgs(String name, double value)
        {
            this.name = name;
            this.value = value;
        }
        public String name { get; set; }
        public double value { get; set; }
    }
}
