using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
class BasicSimulation : ISimulation
{
    private string FILEPATH = @"../../../Simvars/sysVars.txt";

    public string getVarFilePath()
    {
        return FILEPATH;
    }

    public PlatformPosition simulate(Hashtable t)
    {
        PlatformPosition pp = PlatformPosition.neutralPosition();
        object PlanePitchDegrees = t["PLANE PITCH DEGREES"];
        object PlaneBankDegrees = t["PLANE BANK DEGREES"];

        if (PlaneBankDegrees == null || PlanePitchDegrees == null)
        {
            return pp;
        }

        pp.v = boundAngle(radiansToDegrees(PlanePitchDegrees));
        pp.w = boundAngle(inverse(radiansToDegrees(PlaneBankDegrees)));
        return pp;
    }

    private int boundAngle(int a)
    {
        if(a > 15)
        {
            return 15;
        }else if (a < -15)
        {
            return -15;
        }
        else
        {
            return a;
        }
    }

    private static double RtoDCONVFACT = (180 / Math.PI);
    private int radiansToDegrees(object x)
    {
        return (int)(RtoDCONVFACT * (double)x);
    }

    private int inverse(int x)
    {
        return -1 * x;
    }
}
