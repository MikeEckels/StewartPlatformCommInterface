using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;


class QuadMapSimulation : ISimulation
{
    private string FILEPATH = @"../../../Simvars/QuadMap.txt";

    public string getVarFilePath()
    {
        return FILEPATH;
    }

    static int MAX_SYM_BODYACCEL = 30; //this is a guess
    static int MIN_SYM_BODYACCEL = -30; //this is a guess;
    static int MAX_PLAT_POS = 460;
    static int MIN_PLAT_POS = -460;

    //Platform Tilt Max & Min
    static int MAX_PLAT_ANG = 15;
    static int MIN_PLAT_ANG = -15;

    public PlatformPosition simulate(Hashtable t)
    {
        PlatformPosition pp = PlatformPosition.neutralPosition();

        double PlanePitchDegrees = (double)t["PLANE PITCH DEGREES"];
        double PlaneBankDegrees = (double)t["PLANE BANK DEGREES"];
        double accelX = (double)t["ACCELERATION BODY X"];
        double accelY = (double)t["ACCELERATION BODY Y"];
        double accelZ = (double)t["ACCELERATION BODY Z"];

        if (accelX == null) { return pp; }


        pp.v = bound(radiansToDegrees(PlanePitchDegrees), MIN_PLAT_ANG, MAX_PLAT_ANG);
        pp.w = bound(inverse(radiansToDegrees(PlaneBankDegrees)), MIN_PLAT_ANG, MAX_PLAT_ANG);


        //do i need the bound???
        pp.x = (int) quadraticMap(bound(accelX, MIN_SYM_BODYACCEL, MAX_SYM_BODYACCEL), MIN_SYM_BODYACCEL, MAX_SYM_BODYACCEL, MIN_PLAT_POS,MAX_PLAT_POS);
        pp.y= (int)quadraticMap(bound((accelZ, MIN_SYM_BODYACCEL, MAX_SYM_BODYACCEL), MIN_SYM_BODYACCEL, MAX_SYM_BODYACCEL, MIN_PLAT_POS,MAX_PLAT_POS);


        return pp;
    }

    private double bound(double input, double min, double max)
    {
        if(input < min)
        {
            return min;
        }else if (input > max)
        {
            return max;
        }
        else
        {
            return input;
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

    private double quadraticMap(double input, double in_min, double in_max, double out_min, double out_max)
    {
        return ((input^2) - (in_min^2)) * (out_max - out_min) / ((in_max^2) - in_min) + out_min;
    }
}
