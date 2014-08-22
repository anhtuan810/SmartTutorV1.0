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
using System.Windows.Threading;
using System.IO;

namespace GUI
{
	/// <summary>
	/// Interaction logic for ucPractice.xaml
	/// </summary>
	public partial class ucPractice_FullScreen : UserControl
	{
        private RequiredInterface.GUIRecorderInterface interface_recorder = new RequiredInterface.GUIRecorderInterface();
        DispatcherTimer timer_kinect = new DispatcherTimer();
        private DateTime time_start_recording;


        public ucPractice_FullScreen()
		{
			this.InitializeComponent();
            timer_kinect.Tick += timer_kinect_Tick;
            timer_kinect.Interval = new TimeSpan(0, 0, 0, 0, 30);
            timer_kinect.Start();

            string folder_parent = CreateFolderData();

            interface_recorder.TurnOnKinectSensor();
            interface_recorder.StartRecordingONI(folder_parent + "kinect_data.oni");
            interface_recorder.TurnOn_StartRecording_Webcam(0, 0, folder_parent + "webcam_data.avi");
            time_start_recording = DateTime.Now;
		}


        void timer_kinect_Tick(object sender, EventArgs e)
        {
            this.imgKinect.Source = interface_recorder.GrabFrameKinect();
            DateTime time_now = DateTime.Now;
            TimeSpan current_duration = time_now - time_start_recording;
            this.lblTime.Content = current_duration.ToString(@"d\.hh\:mm\:ss");
            //this.lblTime.Content = current_duration.Hours.ToString() + ":" + current_duration.Minutes.ToString() + ":" + current_duration.Seconds.ToString();
        }


        private void lblTime_MouseDown(object sender, MouseButtonEventArgs e)
        {
            timer_kinect.Stop();
            interface_recorder.StopRecordingONI();
            interface_recorder.TurnOffKinectSensor();

            interface_recorder.StopRecording_Webcam();
            interface_recorder.TurnOffWebcam();

            // Switch to the result window
            frmMain main_form = (frmMain)((Grid)this.Parent).Parent;
            main_form.SwitchWindow(ContentInMainForm.Result);
        }


        private string CreateFolderData()
        {
            string folder_parent = Shared.Constants.kDataFolder + DateTime.Now.ToLocalTime().Ticks.ToString() + @"\";
            if (!Directory.Exists(folder_parent))
            {
                Directory.CreateDirectory(folder_parent);
            }

            string folder_features = folder_parent + @"features\";
            if (!Directory.Exists(folder_features))
            {
                Directory.CreateDirectory(folder_features);
            }

            string folder_result = folder_parent + @"result\";
            if (!Directory.Exists(folder_result))
            {
                Directory.CreateDirectory(folder_result);
            }
            return folder_parent;
        }
	}
}