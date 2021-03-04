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

        protected override void DefWndProc(ref Message m)
        {
            if (!sc.handleDef(ref m))
            {
                base.DefWndProc(ref m);
            }
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            sc.control(this.Handle);
        }

        private void Form1_FormClosing(object sender, FormClosingEventArgs e)
        {
            sc.dispose();
        }
    }
}
