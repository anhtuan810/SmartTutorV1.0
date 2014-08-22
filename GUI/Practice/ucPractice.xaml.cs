using System;
using System.Collections.Generic;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Timers;
using System.Windows.Threading;

namespace GUI
{
	/// <summary>
	/// Interaction logic for ucPractice.xaml
	/// </summary>
	public partial class ucPractice : UserControl
	{
        private RequiredInterface.GUIRecorderInterface interface_recorder = new RequiredInterface.GUIRecorderInterface();
        DispatcherTimer timer_kinect = new DispatcherTimer();

		public ucPractice()
		{
			this.InitializeComponent();
            timer_kinect.Tick += timer_kinect_Tick;
            timer_kinect.Interval = new TimeSpan(0, 0, 0, 0, 30);
            timer_kinect.Start();

            interface_recorder.TurnOnKinectSensor();
            

            //for (int i = 0; i < 100; i++ )
            //{
            //    this.imgKinect.Source = recorder_interface.GrabFrame();
            //}
		}

        void timer_kinect_Tick(object sender, EventArgs e)
        {
            this.imgKinect.Source = interface_recorder.GrabFrameKinect();
        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            timer_kinect.Stop();
            interface_recorder.TurnOffKinectSensor();
        }

        private void btnStartPracticing_Click(object sender, RoutedEventArgs e)
        {
            // Switch to the full screen
            timer_kinect.Stop();
            interface_recorder.TurnOffKinectSensor();
            frmMain main_form = (frmMain)((Grid)this.Parent).Parent;
            main_form.SwitchWindow(ContentInMainForm.Practice_FullScreen);
        }
	}
}