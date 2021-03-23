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
    private PlatformController pc;
    private AccelerationSmoother acs;

    private int REQUEST_FREQ = 2; //milliseconds
    private bool isConnected = false;

    public SystemController(){
        s = new QuadMapSimulation();
        acs = new AccelerationSmoother();


        sq = new SysQuerierImp(s.getVarFilePath());
        sq.DataDispatch += symResponded;
        sq.setRequestFreq(REQUEST_FREQ);

        pc = new PlatformController(new Platform());

        pc.initialize();
    }
 

    private void symResponded(object sender, EventArgs e)
    {
        var data = (DequeueEventArgs)e;
        Hashtable t = data.t;

        PlatformPosition pp = s.simulate(t);
        pc.newPosition(pp);        
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