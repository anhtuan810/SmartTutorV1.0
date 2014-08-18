using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using DirectX.Capture;

namespace RecorderAVI
{
    public partial class Form1 : Form
    {
        Filters filters = new Filters();
        Capture capture = null;

        public Form1()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            filters = new Filters();
            capture = new Capture(filters.VideoInputDevices[0], filters.AudioInputDevices[0]);
            capture.Filename = "C:\\2.avi";
            capture.VideoCompressor = filters.VideoCompressors[0];
            capture.AudioCompressor = filters.AudioCompressors[0];
            capture.Start();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            capture.Stop();
            capture.Dispose();
        }
    }
}
