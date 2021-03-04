using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;


class VelAccelSimulation : ISimulation
{
    private string FILEPATH = @"D:/Documents/GitHub/StewartPlatformCommInterface/VelAccel.txt";

    public string getVarFilePath()
    {
        return FILEPATH;
    }

    public PlatformPosition simulate(Hashtable t)
    {
        PlatformPosition pp = PlatformPosition.neutralPosition();
        object rotatVelX = t["ROTATIONAL VELOCITY BODY X"];
        object rotatVelY = t["ROTATIONAL VELOCITY BODY Y"];
        object rotatVelZ = t["ROTATIONAL VELOCITY BODY Z"];
        object accelX = t["ACCELERATON BODY X "];
        object accelY = t["ACCELERATON BODY Y "];
        object accelZ = t["ACCELERATON BODY Z "];


        pp.v = mapRotationalVelocity(rotatVelX);
        pp.u = mapRotationalVelocity(rotatVelY);
        pp.w = mapRotationalVelocity(rotatVelZ);

        pp.x = mapPosAccel(accelX);
        pp.y = mapPosAccel(accelY);
        pp.z = mapPosAccel(accelZ);

        return pp;
    }

    static int MAX_SYM_BODYACCEL = 3; //this is a guess
    static int MIN_SYM_BODYACCEL = -3; //this is a guess;
    static int MAX_PLAT_POS = 100;
    static int MIN_PLAT_POS = -100;
    private int mapPosAccel(object bodyAccel){
        double boundedAccel = boundBodyAccel(bodyAccel);
        return (int)(boundedAccel/MAX_SYM_BODYACCEL * MAX_PLAT_POS);
    }

    private double boundBodyAccel(object bodyAccel){
        double bA = (double) bodyAccel;
        if(bA > MAX_SYM_BODYACCEL){
            return (double)MAX_SYM_BODYACCEL;
        }else if(bA < MIN_SYM_BODYACCEL){
            return (double)MIN_SYM_BODYACCEL;
        }else{
            return bA;
        }
    }


    static int MAX_SYM_ROTVEL = 20; //this is a guess
    static int MIN_SYM_ROTVEL = -20; //this is a guess;
    static int MAX_PLAT_ANG = 15;
    static int MIN_PLAT_ANG = -15;
    private int mapRotationalVelocity(object rotVel){
        double boundedRotVel = boundRotVel(rotVel);

        return (int)(boundedRotVel/MAX_SYM_ROTVEL * MAX_PLAT_ANG);
    }

    private double boundedRotVel(object rotVel){
        double rV = (double)rotVel;
        if(rV > MAX_SYM_ROTVEL){
            return (double)MAX_SYM_ROTVEL;
        }else if(rV< MIN_SYM_ROTVEL){
            return (double) MIN_SYM_ROTVEL;
        }else{
            return rV;
        }
    }
}
