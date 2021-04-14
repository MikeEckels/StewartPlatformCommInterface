using PlatformLibrary;
using System;
using System.Collections.Generic;

class PlatformController{
    private Platform p;
<<<<<<< HEAD
    private const double MAX_ACCEl = 100; //m/s^2
=======
    private const double MAX_ACCEL = 18; //m/s^2
>>>>>>> IntegrationBranchFixes
    private TimeDepPosition lastPos;

    public PlatformController(Platform p){
        this.p = p;
    }

    public void initialize(){
        PlatformPosition initial = PlatformPosition.neutralPosition();
        lastPos = new TimeDepPosition(initial);
        p.SetFunctionCode(0x1401);//Relative time
        p.SetChannelCode(1);//Six axis mode
        p.SetMoveTimeMs(1); //Request Freq / 2. Should not hardcode this. Need a getter.
        setPosition(initial);
        p.Move();
    }

    public void newPosition(PlatformPosition pp){
        TimeDepPosition newPos = new TimeDepPosition(pp);
        newPos = adjustAccelerations(lastPos, newPos);
        lastPos = newPos;
        if(!setPosition(newPos.pp)){Console.WriteLine("Invalid Position"); return;}
        p.Move();
    }

    private bool setPosition(PlatformPosition pp){
        return p.SetPosition(pp.x,pp.y,pp.z,pp.u,pp.v,pp.w);
    }


    private TimeDepPosition adjustAccelerations(TimeDepPosition oldp, TimeDepPosition newp){
        TimeDepPosition returnPos = newp;
        long deltaT = newp.time_milli - oldp.time_milli;
        Translations t = new Translations(newp.pp, oldp.pp);

        foreach (var trans in t.getArr())
<<<<<<< HEAD
        {
            if (trans.calcAccel(deltaT) > MAX_ACCEl){
                trans.meetAccelSpec(MAX_ACCEl, deltaT);
=======
        {   
            if(trans.calcAccel(deltaT) > MAX_ACCEL){
                trans.meetAccelSpec(MAX_ACCEL, deltaT);
>>>>>>> IntegrationBranchFixes
            }
        }
        returnPos.pp = t.buildPlatPositionObject();
        return returnPos;
    }

}
class Translations{
    private List<Translation> t = new List<Translation>();
    public Translations(PlatformPosition newp, PlatformPosition oldp){
        t.Add(new Translation(newp.x, oldp.x));
        t.Add(new Translation(newp.y, oldp.y));
        t.Add(new Translation(newp.z, oldp.z));
        t.Add(new Translation(newp.u, oldp.u));
        t.Add(new Translation(newp.v, oldp.v));
        t.Add(new Translation(newp.w, oldp.w));
    }

    public List<Translation> getArr(){
        return t;
    }

    public PlatformPosition buildPlatPositionObject(){
        return new PlatformPosition(t[0].getLast(), t[1].getLast(), t[2].getLast(), t[3].getLast(), t[4].getLast(), t[5].getLast());
    }
}


class TimeDepPosition{
    public PlatformPosition pp;
    public long time_milli;

    public TimeDepPosition(PlatformPosition pp){
        this.pp = pp;
        this.time_milli = calcCurrTime();
    }

    private long calcCurrTime(){
        return DateTime.Now.Ticks / TimeSpan.TicksPerMillisecond;
    }
}


class Translation{
    private int first;
    private int last;

    public Translation(int last, int first){
        this.last = last;
        this.first = first;
    }

    public double calcAccel(long t_milli){
<<<<<<< HEAD
        return Math.Abs(1000 * (last - first) / Math.Pow(t_milli, 2));
    }

    public void meetAccelSpec(double maxAccel, long t_milli)
    {
        int tempCalc = (int)(((maxAccel * Math.Pow(t_milli, 2))/ 1000) + this.first);
        if (this.last < 0)
        {
            this.last = tempCalc * -1;
        }
        else
        {
            this.last = tempCalc;
        }
=======
        return Math.Abs(((2 * ((last - first) / 1000)) / (Math.Pow((t_milli / 1000), 2))));
    }

    public int meetAccelSpec(double maxAccel, long t_milli){
        return this.last = (int)(((0.5) * (maxAccel) * (Math.Pow((t_milli / 1000), 2)) + (this.first / 1000)) * 1000);
>>>>>>> IntegrationBranchFixes
    }

    public int getLast(){
        return this.last;
    }
}