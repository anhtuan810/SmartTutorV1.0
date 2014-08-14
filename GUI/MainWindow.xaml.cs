using System;
using System.Collections.Generic;
using System.Linq;
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

// Allow managed code to call unmanaged functions that are implemented in a DLL
using System.Runtime.InteropServices;
using System.Windows.Media.Imaging;

namespace GUI
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public unsafe partial class MainWindow : Window
    {
        [DllImport(@"InterfaceForGUI.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void TurnOnKinectSensor();


        [DllImport(@"InterfaceForGUI.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void StartRecordingONI(string file_name);


        [DllImport(@"InterfaceForGUI.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void StopRecordingONI();


        [DllImport(@"InterfaceForGUI.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void TurnOffKinectSensor();





        [DllImport(@"InterfaceForGUI.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr GrabFrame();




        public MainWindow()
        {
            InitializeComponent();
        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            //c = Add(c, c);
            TurnOnKinectSensor();
            string file_name = "C:\\final Test.oni";
            StartRecordingONI(file_name);
        }

        private void Button_Click_1(object sender, RoutedEventArgs e)
        {
            StopRecordingONI();
            TurnOffKinectSensor();
        }

        private void Button_Click_2(object sender, RoutedEventArgs e)
        {
            TurnOnKinectSensor();

            // Grab data
            IntPtr data = GrabFrame();
            byte[] buffer = new byte[640 * 480 * 3];
            Marshal.Copy(data, buffer, 0, buffer.Length);

            // Create colour image out of data

            WriteableBitmap bitmap = new WriteableBitmap(640, 480, 96.0, 96.0, PixelFormats.Rgb24, null);
            bitmap.WritePixels(new Int32Rect(0, 0, 640, 480), buffer, 640 * 3, 0);
            this.image.Source = bitmap;

            TurnOffKinectSensor();
        }
    }
}
