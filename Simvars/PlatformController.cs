using PlatformLibrary;
using System;
using System.Collections;
using System.Collections.Generic;

class PlatformController{
    private Platform p;
    private const double MAX_ACCEl = 1; //m/s^2
    private TimeDepPosition lastPos;

    public PlatformController(Platform p){
        this.p = p;
        q= new Queue<TimeDepPosition>(MAX_QUEUE_COUNT);
    }

    public void initialize(){
        PlatformPosition initial = PlatformPosition.neutralPosition();
        lastPos = new TimeDepPosition(initial);
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
        return p.setPosition(pp.x,pp.y,pp.z,pp.u,pp.v,pp.w);
    }


    private TimeDepPosition adjustAccelerations(TimeDepPosition old, TimeDepPosition new){
        TimeDepPosition returnPos = new;
        long deltaT = new.time_milli - old.time_milli;
        Translations t = new Translations(new.pp, old.pp);

        foreach (var trans in t.getArr())
        {   
            if(trans.calcAccel(deltaT) > MAX_ACCEl){
                trans.meetAccelSpec(MAX_ACCEl, deltaT);
            }
        }
        returnPos.pp = t.buildPlatPositionObject();
    }

}
class Translations{
    private Translation[] t;
    public Translations(PlatformPosition new, PlatformPosition old){
        t = {
            new Translation(new.x, old.x),
            new Translation(new.y, old.y),
            new Translation(new.z, old.z),
            new Translation(new.u, old.u),
            new Translation(new.v, old.v),
            new Translation(new.w, old.w)
        }
    }

    public Translation[] getArr(){
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
        return Math.Abs(200 * (last - first) / Math.Pow(t_milli, 2));
    }

    public double meetAccelSpec(double maxAccel, long t_milli){
        this.last = (maxAccel * Math.Pow(t_milli,2) / 200) + this.first;
    }

    public int getLast(){
        return this.last;
    }
}