using System;

namespace SimWatcher
{
    class SystemController
    {   
        private SysQuerierImp sysStateQuer;
        private State sysState;
        private int queryFreq = 10;

        public SystemController(){
            sysStateQuer = new SysQuerierImp(Resources.SysControlVars);
            sysStateQuer.setRequestFreq = 1000;
            sq.DataDispatch += handleSimResponse;
            sysState = new WaitingState();
        }

        private void updateState(double decisionVal){
            switch(decisionVal){
                case 0: sysState = new SimulateState(); break;
                case 1: sysState = new CalibrateState(); break; 
                case 2: sysState = new ResetState(); break;
                default: sysState = new WaitingState();
            }
        }

        private void handleSimResponse(object sender, EventArgs e)
        {
            var data = (DequeueEventArgs)e;
            Hashtable t = data.t;
            // foreach(string key in t.Keys)
            // {
            //     Console.WriteLine(key + ": " + t[key]);
            // }
            updateState(t["Some var"]);
        }
    }
}
