using PlatformLibrary;
using System;
using System.Collections;
using System.Collections.Generic;

class PlatformController{
    private Platform p;
    private Queue<TimeDepPosition> q;
    private const int MAX_QUEUE_COUNT = 2;
    private const double MAX_ACCEl = 9.81; //m/s^2

    public PlatformController(Platform p){
        this.p = p;
        q= new Queue<TimeDepPosition>(MAX_QUEUE_COUNT);
    }

    public void initialize(){
        PlatformPosition initial = PlatformPosition.neutralPosition();
        newPosition(initial);
        p.SetPosition(initial.x, initial.y, initial.z, initial.u, initial.v, initial.w);
        p.Move();
    }

    public void newPosition(PlatformPosition pp){
        q.Enqueue(new TimeDepPosition(pp));
        if(acValid() && p.SetPosition(pp.x,pp.y,pp.z,pp.u,pp.v,pp.w)){
            p.Move();
            return;
        }
        Console.WriteLine("Move not valid");
    }

    private bool acValid(){
        TimeDepPosition tdp1 = q.Dequeue();
        TimeDepPosition tdp2 = q.Peek();
        long deltaT = tdp2.time_milli - tdp1.time_milli;

        Translation[] translations = {new Translation(tdp1.pp.x,tdp2.pp.x),
                                      new Translation(tdp1.pp.y, tdp2.pp.y),
                                      new Translation(tdp1.pp.z, tdp2.pp.z)};
        for(int i = 0; i < translations.Length; i++){
            if(translations[i].calcAccel(deltaT) > MAX_ACCEl){
                return false;
            }
        }
        return true;
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
    private int pos1;
    private int pos2;

    public Translation(int pos1, int pos2){
        this.pos1 = pos1;
        this.pos2 = pos2;
    }

    public double calcAccel(long t_milli){
        return 2000 * (pos2 - pos1) / Math.Pow(t_milli, 2);
    }
}