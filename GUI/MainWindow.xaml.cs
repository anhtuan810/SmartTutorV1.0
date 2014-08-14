//
//  Smart Tutor v1.0
//	GUI
//
//  Created: 
//
//  Copyright (c) 2014 Anh Tuan Nguyen. All rights reserved.
//

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
using GUI.RequiredInterface;

namespace GUI
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        GUIRecorderInterface IRecorder = new GUIRecorderInterface();

        public MainWindow()
        {
            InitializeComponent();
        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            IRecorder.TurnOnKinectSensor();
        }

        private void Button_Click_1(object sender, RoutedEventArgs e)
        {
            IRecorder.TurnOffKinectSensor();
        }

        private void Button_Click_2(object sender, RoutedEventArgs e)
        {
            this.image.Source = IRecorder.GrabFrame();
        }
    }
}
