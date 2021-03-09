using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
interface ISimulation
{
    PlatformPosition simulate(Hashtable t);
    string getVarFilePath();
}
