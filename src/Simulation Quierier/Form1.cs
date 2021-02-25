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
        SystemController sc;
        public Form1()
        {
            InitializeComponent();
            sc = new SystemController();
        }

        private void Form1_Loaded(object sender, FormLoadedEventArgs e){
            sc.control();
        }
        
        // The case where the user closes the client
        private void Form1_FormClosed(object sender, FormClosedEventArgs e)
        {
            sc.dispose();
        }

        protected override void DefWndProc(ref Message m)
        {
            if(!sc.handleDef(ref m))
            {
                base.DefWndProc(ref m);
            }
        }
    }
}
