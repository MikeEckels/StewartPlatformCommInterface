using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;


class VelAccelSimulation : ISimulation
{
    private const string FILEPATH = @"../../../Simvars/VelAccel.txt";

    public string getVarFilePath()
    {
        return FILEPATH;
    }

    public PlatformPosition simulate(Hashtable t)
    {
        PlatformPosition pp = PlatformPosition.neutralPosition();

        //object rotateVelX = t["ROTATION VELOCITY BODY X"];
        //object rotateVelY = t["ROTATION VELOCITY BODY Y"];
        //object rotateVelZ = t["ROTATION VELOCITY BODY Z"];
        object PlanePitchDegrees = t["PLANE PITCH DEGREES"];
        object PlaneBankDegrees = t["PLANE BANK DEGREES"];
        object accelX = t["ACCELERATION BODY X"];
        object accelY = t["ACCELERATION BODY Y"];
        object accelZ = t["ACCELERATION BODY Z"];

        Console.WriteLine("Acceleration Input Z: " + accelZ);

        if (accelX == null) { return pp; }

        //Console.WriteLine("Input: " + rotateVelX);

        //pp.v = mapRotationalVelocity(rotateVelX);
        //pp.u = mapRotationalVelocity(rotateVelY);
        //pp.w = mapRotationalVelocity(rotateVelZ);

        pp.v = boundAngle(radiansToDegrees(PlanePitchDegrees));
        pp.w = boundAngle(inverse(radiansToDegrees(PlaneBankDegrees)));
        //no yaw... YET

        //bound input accel +- 30
        //map bounded input to a specific axis min/max
        //possible scalling

        Console.WriteLine("AccelX: " + (double) accelX + "|  AccelZ: " + (double) accelZ);

        pp.x = (int) map(bound((double)accelX, MIN_SYM_BODYACCEL, MAX_SYM_BODYACCEL), MIN_SYM_BODYACCEL, MAX_SYM_BODYACCEL, -200,200);
        pp.y= (int)map(bound((double)accelZ, MIN_SYM_BODYACCEL, MAX_SYM_BODYACCEL), MIN_SYM_BODYACCEL, MAX_SYM_BODYACCEL, -200, 200) * 20;
        //pp.z = (int)map(bound((double)accelY, MIN_SYM_BODYACCEL, MAX_SYM_BODYACCEL), MIN_SYM_BODYACCEL, MAX_SYM_BODYACCEL, 0, 460);



        //pp.x = mapPosAccel(accelX);
        //pp.y = mapPosAccel(accelY);
        //pp.z = mapPosAccel(accelZ);


        //Console.WriteLine("Output:" + pp.z);

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


    private int boundAngle(int a)
    {
        if (a > 15)
        {
            return 15;
        }
        else if (a < -15)
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




    static int MAX_SYM_BODYACCEL = 30; //this is a guess
    static int MIN_SYM_BODYACCEL = -30; //this is a guess;
    static int MAX_PLAT_POS = 460;
    static int MIN_PLAT_POS = -460;
    //private int mapPosAccel(object bodyAccel){
    //    double boundedAccel = boundBodyAccel((double)bodyAccel * .5);
    //    return (int)map(boundedAccel, MIN_SYM_BODYACCEL, MAX_SYM_BODYACCEL, MIN_PLAT_POS, MAX_PLAT_POS);
    //}

    //private double boundBodyAccel(object bodyAccel){
    //    double bA = (double) bodyAccel;
    //    if(bA > MAX_SYM_BODYACCEL){
    //        return (double)MAX_SYM_BODYACCEL;
    //    }else if(bA < MIN_SYM_BODYACCEL){
    //        return (double)MIN_SYM_BODYACCEL;
    //    }else{
    //        return bA;
    //    }
    //}


    //static int MAX_SYM_ROTVEL = 20; //this is a guess
    //static int MIN_SYM_ROTVEL = -20; //this is a guess;
    //static int MAX_PLAT_ANG = 15;
    //static int MIN_PLAT_ANG = -15;
    //private int mapRotationalVelocity(object rotVel){

    //    double boundedRotVel = boundRotVel((double)rotVel * 10);

    //    return (int)(map(boundedRotVel, MIN_SYM_ROTVEL, MAX_SYM_ROTVEL, MIN_PLAT_ANG, MAX_PLAT_ANG)/10);
    //}

    //private double boundRotVel(object rotVel){
    //    double rV = (double)rotVel;
    //    if(rV > MAX_SYM_ROTVEL){
    //        return (double)MAX_SYM_ROTVEL;
    //    }else if(rV< MIN_SYM_ROTVEL){
    //        return (double) MIN_SYM_ROTVEL;
    //    }else{
    //        return rV;
    //    }
    //}

    private double map(double input, double in_min, double in_max, double out_min, double out_max)
    {
        return (input - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
    }
}
