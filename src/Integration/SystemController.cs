interface ISystemController{
    void control();
    void dispose();
    void handleDef(ref Message m);
    void setFormHandle(IntPtr ptr);
}

public class SystemController : ISystemController{
    private IntPtr formHandle;
    private SysQuerierImp sq;
    private Simulation s;
    private Platform p;

    private int REQUEST_FREQ = 2; //milliseconds
    private bool isConnected = false;

    public SystemController(){
        s = new BasicSimulation();

        sq = new SysQuerierImp(s.getVarFilePath(), new QueryDiagnostics());
        sq.DataDispatch += symResponded;
        sq.setRequestFreq(REQUEST_FREQ);

        p = new Platform();
    }
 

    private void symResponded(object sender, EventArgs e)
    {
        var data = (DequeueEventArgs)e;
        Hashtable t = data.t;

        PlatformPosition pp = s.simulate(t);
        p.setPosition(pp);
        p.move();
    }

    public void control(){
       if(formHandle == null){
           Console.WriteLine("You must specify the form handle before connecting to the Sim");
           return;
       }

       isConnected = sq.connectToSim(formHandle);
       Console.WriteLine("The Simulation is connected:____ " + isConnected + "_____")
    }

    public void dispose(){
        isConnected = sq.disconnectFromSim();
    }


    public void handleDef(ref Message m){
        sq.handleDef(m);
    }

    public void setFormHandle(IntPtr ptr){
        this.formHandle = ptr;
    }
}