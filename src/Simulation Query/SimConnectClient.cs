using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Microsoft.FlightSimulator.SimConnect;
using System.Runtime.InteropServices;
using System.Windows.Forms;
using System.Collections.ObjectModel;

namespace SimWatcher
{
	interface SimConnectClientInterface{
		bool attempClientConnect(IntPtr ptr);
		bool disconnectFromSim();
		void requestSimData();
		void addDataRequest(String varName, String varUnits);
	}

    public enum DEFINITIONS
    {
        Struct1,
    }

    public enum DATA_REQUESTS
    {
        REQUEST_1,
    };

    public delegate void Notify(object sender, EventArgs e);  // delegate

    

    class SimConnectClient : SimConnectClientInterface
	{
		private SimConnect simconnect;
    	// User-defined win32 event
        const int WM_USER_SIMCONNECT = 0x0402;
        public ObservableCollection<SimvarRequest> lSimvarRequests { get; private set; }
        public ObservableCollection<uint> lObjectIDs { get; private set; }

        private IntPtr ptr = new IntPtr(0);

        public event Notify DataReceived;

        public SimConnectClient(){
        	lSimvarRequests = new ObservableCollection<SimvarRequest>();

            lObjectIDs = new ObservableCollection<uint>();
            lObjectIDs.Add(1);
        }

		public bool attempClientConnect(IntPtr ptr)
        {
            if (simconnect == null)
            {
                try
                {
                    // the constructor is similar to SimConnect_Open in the native API
                    simconnect = new SimConnect("Managed Data Request", ptr, WM_USER_SIMCONNECT, null, 0);
                    setUpEventHandlers();


                    return true;
                }
                catch (COMException ex)
                {
                    Console.WriteLine("Unable to connect to Sim");
                    Console.WriteLine(ex);
                    return false;
                }
            }
            else
            {
                Console.WriteLine("Error try again");
                disconnectFromSim();
                return false;
            }
        }

        public bool disconnectFromSim()
        {
            if (simconnect != null)
            {
                // Dispose serves the same purpose as SimConnect_Close()
                simconnect.Dispose();
                simconnect = null;
                Console.WriteLine("Disconnected From Sim");
                return true;
            }
            return false;
        }

        private int m_iCurrentDefinition = 0;
        private int m_iCurrentRequest = 0;
        private string m_sUnitRequest = null;
        private uint m_iIndexRequest = 0;
        private string m_sSimvarRequest = null;
        
        public void addDataRequest(string _sOverrideSimvarRequest, string _sOverrideUnitRequest)
        {
            Console.WriteLine("AddRequest");

            string sNewSimvarRequest = _sOverrideSimvarRequest != null ? _sOverrideSimvarRequest : ((m_iIndexRequest == 0) ? m_sSimvarRequest : (m_sSimvarRequest + ":" + m_iIndexRequest));
            string sNewUnitRequest = _sOverrideUnitRequest != null ? _sOverrideUnitRequest : m_sUnitRequest;

            SimvarRequest oSimvarRequest = new SimvarRequest
            {
                eDef = (DEFINITIONS)m_iCurrentDefinition,
                eRequest = (DATA_REQUESTS)m_iCurrentRequest,
                sName = sNewSimvarRequest,
                sUnits = sNewUnitRequest
            };

            oSimvarRequest.bPending = !RegisterToSimConnect(oSimvarRequest);
            oSimvarRequest.bStillPending = oSimvarRequest.bPending;

            lSimvarRequests.Add(oSimvarRequest);

            ++m_iCurrentDefinition;
            ++m_iCurrentRequest;
        }

        public void requestSimData()
        {
            foreach (SimvarRequest oSimvarRequest in lSimvarRequests)
            {
                if (!oSimvarRequest.bPending)
                {
                    simconnect?.RequestDataOnSimObjectType(oSimvarRequest.eRequest, oSimvarRequest.eDef, 0, SIMCONNECT_SIMOBJECT_TYPE.USER);
                    oSimvarRequest.bPending = true;
                }
                else
                {
                    oSimvarRequest.bStillPending = true;
                }
            }
            //Console.WriteLine("Request Sent");
        }

        public bool handleDefWndProc(ref Message m)
        {
            if (m.Msg == WM_USER_SIMCONNECT)
            {
                if (simconnect != null)
                {
                    simconnect.ReceiveMessage();
                    return true;
                }
            }
            return false;
        }

        public bool bObjectIDSelectionEnabled
        {
            get { return m_bObjectIDSelectionEnabled; }
            //set { this.SetProperty(ref m_bObjectIDSelectionEnabled, value); }
        }
        private bool m_bObjectIDSelectionEnabled = false;
        private uint m_iObjectIdRequest = 0;
        private void simconnect_OnRecvSimobjectDataBytype(SimConnect sender, SIMCONNECT_RECV_SIMOBJECT_DATA_BYTYPE data)
        {
            uint iRequest = data.dwRequestID;
            uint iObject = data.dwObjectID;
            if (!lObjectIDs.Contains(iObject))
            {
                lObjectIDs.Add(iObject);
            }
            foreach (SimvarRequest oSimvarRequest in lSimvarRequests)
            {
                if (iRequest == (uint)oSimvarRequest.eRequest && (!bObjectIDSelectionEnabled || iObject == m_iObjectIdRequest))
                {
                    double dValue = (double)data.dwData[0];
                    oSimvarRequest.dValue = dValue;
                    oSimvarRequest.bPending = false;
                    oSimvarRequest.bStillPending = false;

                    // Console.WriteLine(oSimvarRequest.sName + ": " + dValue);

                    onDataReceived(new DataReceivedEventArgs(oSimvarRequest.sName, dValue));
                }
            }
        }

        protected virtual void onDataReceived(DataReceivedEventArgs e) //protected virtual method
	    {
	        //if ProcessCompleted is not null then call delegate
	        DataReceived?.Invoke(this, e); 
	    }

        private void simconnect_OnRecvOpen(SimConnect sender, SIMCONNECT_RECV_OPEN data)
        {
            Console.WriteLine("Connected To Sim");
            setUpEventHandlers();
            // initDataRequest();
        }

        // The case where the user closes Prepar3D
        private void simconnect_OnRecvQuit(SimConnect sender, SIMCONNECT_RECV data)
        {
            Console.WriteLine("Connection clossed");
            disconnectFromSim();
        }

        private void simconnect_OnRecvException(SimConnect sender, SIMCONNECT_RECV_EXCEPTION data)
        {
            Console.WriteLine("Exception received: " + data.dwException);
        }



        private bool RegisterToSimConnect(SimvarRequest _oSimvarRequest)
        {
            if (simconnect != null)
            {
                /// Define a data structure
                simconnect.AddToDataDefinition(_oSimvarRequest.eDef, _oSimvarRequest.sName, _oSimvarRequest.sUnits, SIMCONNECT_DATATYPE.FLOAT64, 0.0f, SimConnect.SIMCONNECT_UNUSED);
                /// IMPORTANT: Register it with the simconnect managed wrapper marshaller
                /// If you skip this step, you will only receive a uint in the .dwData field.
                simconnect.RegisterDataDefineStruct<double>(_oSimvarRequest.eDef);

                return true;
            }
            else
            {
                return false;
            }
        }

        private void setUpEventHandlers()
        {
            // listen to connect and quit msgs
            simconnect.OnRecvOpen += new SimConnect.RecvOpenEventHandler(simconnect_OnRecvOpen);
            simconnect.OnRecvQuit += new SimConnect.RecvQuitEventHandler(simconnect_OnRecvQuit);

            // listen to exceptions
            simconnect.OnRecvException += new SimConnect.RecvExceptionEventHandler(simconnect_OnRecvException);

            // catch a simobject data request
            simconnect.OnRecvSimobjectDataBytype += new SimConnect.RecvSimobjectDataBytypeEventHandler(simconnect_OnRecvSimobjectDataBytype);
        }

        private void initDataRequest()
        {
            try
            {


                foreach (SimvarRequest oSimvarRequest in lSimvarRequests)
                {
                    if (oSimvarRequest.bPending)
                    {
                        oSimvarRequest.bPending = !RegisterToSimConnect(oSimvarRequest);
                        oSimvarRequest.bStillPending = oSimvarRequest.bPending;
                    }
                }
                
            }
            catch (COMException ex)
            {
                Console.WriteLine(ex);
            }
        }
	}

	public class SimvarRequest
    {
        public DEFINITIONS eDef = DEFINITIONS.Struct1;
        public DATA_REQUESTS eRequest = DATA_REQUESTS.REQUEST_1;

        public string sName { get; set; }

        public double dValue;

        private double m_dValue = 0.0;

        public string sUnits { get; set; }

        public bool bPending = true;
        public bool bStillPending;
        private bool m_bStillPending = false;
    }

}