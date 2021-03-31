using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Microsoft.FlightSimulator.SimConnect;
using System.Runtime.InteropServices;
using System.Windows.Forms;
using System.Collections.ObjectModel;
using Simvars;
using System.Collections;
using System.Windows.Threading;
using System.Diagnostics;

namespace SimWatcher
{
    interface SysQuerier
    {
        bool connectToSim(IntPtr ptr);
        //void loadRequestVariables();
        void requestSimData(object sender, EventArgs e);
        void setRequestFrequency(TimeSpan time);
        // void printData();
        bool disconnectFromSim();
    }

    class SysQuerierImp : SysQuerier
    {   
        // private string TEST_FILE_LOCATION = @"D:\MSFS SDK\Samples\Test1\sysVars.txt";
        private const int MAX_QUEUE_COUNT = 5;
        private TimeSpan QUERY_TIMER_DEFAULT = new TimeSpan(0, 0, 0, 0, 1); //default to .5 second
        private TimeSpan DEQUEUE_TIMER_DEFAULT = new TimeSpan(0, 0, 0, 0, 2); //default to 1 second


        SimConnectClient scc;
        SysVarLoader svl;
        private DispatcherTimer request_Timer;
        private DispatcherTimer queue_Timer;
        Queue<Hashtable> q;

        public event Notify DataDispatch;


        public SysQuerierImp(String sysVarFileLocation){ //must be absolute path
            scc = new SimConnectClient();
            scc.DataReceived += dataReceived;

            svl = new SysVarLoader();
            svl.setTxtFileLocation(sysVarFileLocation);
            svl.loadSysVariables();

            initializeEventTimers();

            q = new Queue<Hashtable>(MAX_QUEUE_COUNT);
        }

        public void setRequestFreq(int milliseconds){
            DEQUEUE_TIMER_DEFAULT = new TimeSpan(0,0,0,0, milliseconds);
            QUERY_TIMER_DEFAULT = new TimeSpan(0,0,0,0, milliseconds/2);
        }

        public bool handleDef(ref Message m)
        {
            return scc.handleDefWndProc(ref m);
        }

        public void setRequestFrequency(TimeSpan time){
            request_Timer.Interval = time;
        }


        public bool connectToSim(IntPtr ptr){
            if (scc.attempClientConnect(ptr))
            {
                loadRequestVariables();
                request_Timer.Start();
                queue_Timer.Start();

                return true;
            }
            return false;
        }

        public bool disconnectFromSim()
        {
            if (scc.disconnectFromSim())
            {
                request_Timer.Start();
                queue_Timer.Start();
                return true;
            }
            return false;
        }

        private void loadRequestVariables(){
            List<object> varsAndUnits = svl.getVarsAndUnits();
            for(int i =0; i<varsAndUnits.Count; i++){
                keyUnit temp = (keyUnit)varsAndUnits[i];
                scc.addDataRequest(temp.key, temp.unit);
            }
        }
        //DELETE THIS IN FUTURE
        Stopwatch sw = new Stopwatch();
        public void requestSimData(object sender, EventArgs e)
        {
            scc.requestSimData();
            sw.Start();
            Console.WriteLine("Data requested");
            //hashtable should have received all of the data by the next call of this function
            q.Enqueue(svl.getTable());
        }

        private void initializeEventTimers()
        {
            //setup for request timer
            request_Timer = new DispatcherTimer();
            request_Timer.Interval = QUERY_TIMER_DEFAULT;
            request_Timer.Tick += new EventHandler(requestSimData);

            //setup for queue pop timer
            queue_Timer = new DispatcherTimer();
            queue_Timer.Interval = DEQUEUE_TIMER_DEFAULT;
            queue_Timer.Tick += new EventHandler(dispatchDequeue);
        }


        private void dataReceived(object sender, EventArgs e)
        {
            sw.Stop();
            Console.WriteLine("---- Time Elapsed: " + sw.ElapsedMilliseconds + "    ------") ;
            sw.Reset();
            var x = (DataReceivedEventArgs)e;
            svl.setKeyValue(x.name, x.value);
        }

        private void dispatchDequeue(object sender, EventArgs e)
        {
            onDequeue(new DequeueEventArgs(q.Dequeue()));
        }

        protected virtual void onDequeue(DequeueEventArgs e) //protected virtual method
        {
            //if ProcessCompleted is not null then call delegate
            DataDispatch?.Invoke(this, e); 
        }

    }
}
