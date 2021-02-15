using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using Microsoft.FlightSimulator.SimConnect;
using System.Runtime.InteropServices;
using Simvars;
using System.Collections;

namespace SimWatcher
{
    public partial class Form1 : Form
    {
        SysQuerierImp sq;
        public Form1()
        {
            InitializeComponent();
            sq = new SysQuerierImp();
            sq.DataDispatch += dataReceived;

            setButtons(true, false);
        }

        private void dataReceived(object sender, EventArgs e)
        {
            var data = (DequeueEventArgs)e;
            Hashtable t = data.t;
            foreach(string key in t.Keys)
            {
                Console.WriteLine(key + ": " + t[key]);
            }

        }



        private void setButtons(bool bConnect, bool bGet)
        {
            btnConnect.Enabled = bConnect;
            btnRequest.Enabled = bGet;
        }

        

        // The case where the user closes the client
        private void Form1_FormClosed(object sender, FormClosedEventArgs e)
        {
            sq.disconnectFromSim();
        }
        private void btnConnect_Click(object sender, EventArgs e)
        {
            if (sq.connectToSim(this.Handle))
            {
                setButtons(false, true);
            }
            else
            {
                setButtons(true, false);
            }
        }

        private void btnRequest_Click(object sender, EventArgs e)
        {
            //sq.requestSimData();
        }

        

        private void Form1_FormClosed_1(object sender, FormClosedEventArgs e)
        {
            sq.disconnectFromSim();
        }

        protected override void DefWndProc(ref Message m)
        {
            if(!sq.handleDef(ref m))
            {
                base.DefWndProc(ref m);
            }
        }
    }
}
