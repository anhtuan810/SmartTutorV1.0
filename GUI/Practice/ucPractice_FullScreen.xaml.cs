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
        /// <summary>
        /// Current status of the form
        /// </summary>
        enum Status
        {
            Nothing,
            CountingDown,
            Recording
        }


        private RequiredInterface.GUIRecorderInterface interface_recorder = new RequiredInterface.GUIRecorderInterface();
        private DispatcherTimer timer_kinect_ = new DispatcherTimer();
        private DispatcherTimer timer_count_down_ = new DispatcherTimer();
        private DateTime time_start_recording_;
        private Status status_;
        private int count_ = 5;


        public ucPractice_FullScreen()
		{
            this.InitializeComponent();
            DisplayKinectStream();
            status_ = Status.Nothing;
            ChangeLayout();

            timer_kinect_.Tick += timer_kinect_Tick;
            timer_kinect_.Interval = new TimeSpan(0, 0, 0, 0, 30);

            timer_count_down_.Tick += timer_count_down__Tick;
            timer_count_down_.Interval = new TimeSpan(0, 0, 1);            
		}

        ~ucPractice_FullScreen()
        {
            interface_recorder.StopRecordingONI();
            interface_recorder.TurnOffKinectSensor();

            interface_recorder.StopRecording_Webcam();
            interface_recorder.TurnOffWebcam();
        }

        void timer_count_down__Tick(object sender, EventArgs e)
        {
            count_--;
            this.lblCountDown.Content = count_;
            if (count_ == 0)
            {
                status_ = Status.Recording;
                ChangeLayout();
                StartRecording();
                timer_count_down_.Stop();
            }
        }


        void timer_kinect_Tick(object sender, EventArgs e)
        {
            this.imgKinect.Source = interface_recorder.GrabFrameKinect();
            DateTime time_now = DateTime.Now;
            TimeSpan current_duration = time_now - time_start_recording_;
            if (status_ == Status.Recording)
                this.lblTime.Content = current_duration.ToString(@"mm\:ss");
            else
                this.lblTime.Content = "00:00";
            //this.lblTime.Content = current_duration.Hours.ToString() + ":" + current_duration.Minutes.ToString() + ":" + current_duration.Seconds.ToString();
        }


        private void lblTime_MouseDown(object sender, MouseButtonEventArgs e)
        {
            StopRecording();
            status_ = Status.Nothing;
        }

        private void UserControl_Unloaded(object sender, RoutedEventArgs e)
        {
        }

        private void btnStartRecording_Click(object sender, RoutedEventArgs e)
        {
            status_ = Status.CountingDown;
            ChangeLayout();
            this.lblCountDown.Visibility = System.Windows.Visibility.Visible;
            timer_count_down_.Start();
        }


        //-------------------------------------------------------------------------------------
        #region Supporting functions

        private void ChangeLayout()
        {
            if (status_ == Status.Nothing)
            {
                this.btnStartRecording.Visibility = System.Windows.Visibility.Visible;
                this.lblCountDown.Visibility = System.Windows.Visibility.Hidden;
                this.imgKinect.Opacity = 0.5;
            }
            else if (status_ == Status.CountingDown)
            {
                this.btnStartRecording.Visibility = System.Windows.Visibility.Hidden;
                this.lblCountDown.Visibility = System.Windows.Visibility.Visible;
                this.imgKinect.Opacity = 0.5;
            }
            else if (status_ == Status.Recording)
            {
                this.btnStartRecording.Visibility = System.Windows.Visibility.Hidden;
                this.lblCountDown.Visibility = System.Windows.Visibility.Hidden;
                this.imgKinect.Opacity = 1.0;
            }
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

        private void DisplayKinectStream()
        {
            timer_kinect_.Start();
            interface_recorder.TurnOnKinectSensor();
            status_ = Status.Nothing;
        }

        private void StartRecording()
        {
            string folder_parent = CreateFolderData();

            interface_recorder.StartRecordingONI(folder_parent + "kinect_data.oni");
            interface_recorder.TurnOn_StartRecording_Webcam(0, 0, folder_parent + "webcam_data.avi");
            time_start_recording_ = DateTime.Now;

            status_ = Status.Recording;
        }

        private void StopRecording()
        {
            timer_kinect_.Stop();
            interface_recorder.StopRecordingONI();
            interface_recorder.TurnOffKinectSensor();

            interface_recorder.StopRecording_Webcam();
            interface_recorder.TurnOffWebcam();

            // Switch to the result window
            frmMain main_form = (frmMain)((Grid)this.Parent).Parent;
            main_form.SwitchWindow(ContentInMainForm.Result);

            status_ = Status.Nothing;
            ChangeLayout();
        }

        #endregion
        //-------------------------------------------------------------------------------------
    }
}