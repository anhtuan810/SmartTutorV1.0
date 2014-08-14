//
//  Smart Tutor v1.0
//	GUI
//  Required interface for Recorder module
//
//  Created: 2014.08.14
//
//  Copyright (c) 2014 Anh Tuan Nguyen. All rights reserved.
//

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.InteropServices;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows;

namespace GUI.RequiredInterface
{
    public class GUIRecorderInterface
    {
        [DllImport(@"InterfaceForGUI.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern bool ITurnOnKinectSensor();


        [DllImport(@"InterfaceForGUI.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern bool IStartRecordingONI(string file_name);


        [DllImport(@"InterfaceForGUI.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void IStopRecordingONI();


        [DllImport(@"InterfaceForGUI.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ITurnOffKinectSensor();

        [DllImport(@"InterfaceForGUI.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr IGrabFrame();


        public bool TurnOnKinectSensor()
        {
            return ITurnOnKinectSensor();
        }

        public void TurnOffKinectSensor()
        {
            ITurnOffKinectSensor();
        }

        public bool StartRecordingONI(string file_name)
        {
            return IStartRecordingONI(file_name);
        }

        public void StopRecordingONI()
        {
            IStopRecordingONI();
        }

        public WriteableBitmap GrabFrame()
        {
            const int kHeight = 480;
            const int kWidth = 640;

            // Grab data
            IntPtr data = IGrabFrame();
            byte[] buffer = new byte[kHeight * kWidth * 3];
            Marshal.Copy(data, buffer, 0, buffer.Length);

            // Create colour image out of data

            WriteableBitmap bitmap = new WriteableBitmap(kWidth, kHeight, 96.0, 96.0, PixelFormats.Rgb24, null);
            bitmap.WritePixels(new Int32Rect(0, 0, kWidth, kHeight), buffer, kWidth * 3, 0);

            return bitmap;
        }
    }
}
