using Simvars;
using SimWatcher;
using System;
using System.Collections;
using System.Windows.Forms;
using PlatformLibrary;

interface ISystemController{
    void control(IntPtr formHandle);
    void dispose();
    bool handleDef(ref Message m);
}

public class SystemController : ISystemController{
    private SysQuerierImp sq;
    private ISimulation s;
    private Platform p;

    private int REQUEST_FREQ = 2; //milliseconds
    private bool isConnected = false;

    public SystemController(){
        s = new VelAccelSimulation();


        sq = new SysQuerierImp(s.getVarFilePath());
        sq.DataDispatch += symResponded;
        sq.setRequestFreq(REQUEST_FREQ);

        p = new Platform();

        p.SetPosition(0, 0, 230, 0, 0, 0);
        p.Move();
    }
 

    private void symResponded(object sender, EventArgs e)
    {
        var data = (DequeueEventArgs)e;
        Hashtable t = data.t;

        PlatformPosition pp = s.simulate(t);
        pp.printPosition();
        if (p.SetPosition(pp.x, pp.y, pp.z, pp.u, pp.v, pp.w))
        {
            p.Move();
        }else
        {
            Console.WriteLine("**** INVALID MOVE *****");
        }
        
    }

    public void control(IntPtr formHandle){
       isConnected = sq.connectToSim(formHandle);
        Console.WriteLine("The Simulation is connected:____ " + isConnected + "_____");
    }

    public void dispose(){
        isConnected = sq.disconnectFromSim();
    }


    public bool handleDef(ref Message m){
        return sq.handleDef(ref m);
    }
}