using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;


class CubicMapSimulation : ISimulation
{
    private const string FILEPATH = @"../../../Simvars/CubicMap.txt";

    public string getVarFilePath()
    {
        return FILEPATH;
    }

    static int MAX_SYM_BODYACCEL = 5; //this is a guess
    static int MIN_SYM_BODYACCEL = -5; //this is a guess;
    static int MAX_PLAT_POS = 230;
    static int MIN_PLAT_POS = -230;

    //Platform Tilt Max & Min
    static int MAX_PLAT_ANG = 15;
    static int MIN_PLAT_ANG = -15;

    public PlatformPosition simulate(Hashtable t)
    {
        PlatformPosition pp = PlatformPosition.neutralPosition();
        if (t["ACCELERATION BODY X"] == null) { return pp; }

        double PlanePitchDegrees = (double)t["PLANE PITCH DEGREES"];
        double PlaneBankDegrees = (double)t["PLANE BANK DEGREES"];
        double accelX = (double)t["ACCELERATION BODY X"];
        double accelY = (double)t["ACCELERATION BODY Y"];
        double accelZ = (double)t["ACCELERATION BODY Z"];

        pp.v = (int)bound(radiansToDegrees(PlanePitchDegrees), (double)MIN_PLAT_ANG, (double)MAX_PLAT_ANG);
        pp.w = (int)bound(inverse(radiansToDegrees(PlaneBankDegrees)), MIN_PLAT_ANG, MAX_PLAT_ANG);

        //do i need the bound???
        pp.x = (int) bound(cubicMap(accelX, MIN_SYM_BODYACCEL, MAX_SYM_BODYACCEL, MIN_PLAT_POS, MAX_PLAT_POS), MIN_PLAT_POS, MAX_PLAT_POS);
        pp.y = (int) bound(cubicMap(accelY, MIN_SYM_BODYACCEL, MAX_SYM_BODYACCEL, MIN_PLAT_POS, MAX_PLAT_POS), MIN_PLAT_POS, MAX_PLAT_POS);


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
    private double radiansToDegrees(object x)
    {
        return RtoDCONVFACT * (double)x;
    }

    private double inverse(double x)
    {
        return -1 * x;
    }

    private double cubicMap(double input, double in_min, double in_max, double out_min, double out_max)
    {
        return Math.Pow(input, 3) + Math.Pow(input, 2) + input;
    }
}
