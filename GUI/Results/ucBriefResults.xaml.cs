//
//  Smart Tutor v1.0
//	GUI
//
//  Created: 2014.09.04
//
//  Copyright (c) 2014 Anh Tuan Nguyen. All rights reserved.
//

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
using GUI.IO;

namespace GUI
{
	/// <summary>
	/// Interaction logic for ucBriefResults.xaml
	/// </summary>
	public partial class ucBriefResults : UserControl
	{
        private Result result_;
        private string data_folder = @"D:\test data\635452884127274310\";

		public ucBriefResults()
		{
			this.InitializeComponent();

            this.title_bar.UpdateData("RESULT", ContentInMainForm.Home);
            this.media.TimerTrackbar.Tick += timer_trackbar__Tick;

            ResultReader result_reader = new ResultReader();
            result_ = result_reader.ReadData(data_folder + @"result\");
            this.media.LoadVideo(data_folder + "webcam_data.avi");


            this.feature1.InputData(
                "Openness", "Closed", "Average", "Opened",
                "Closed Postures", "Average Openness", "Opened Postures",
                result_.binary_contraction_low_,
                result_.binary_contraction_average_,
                result_.binary_contraction_high_);

            this.feature2.InputData(
                "Energy", "Low", "Average", "High", 
                "Low energy", "Average energy", "High energy",
                result_.binary_energy_low_,
                result_.binary_energy_average_,
                result_.binary_energy_high_
                );

            this.feature3.InputData(
                "Stability", "Lean left", "Balanced", "Lean Right",
                "Leaning to the left", "Balanced, good posture", "Leaning to the right",
                result_.binary_lean_left_,
                result_.binary_balanced_,
                result_.binary_lean_right_
                );

            //    "Stability", "Left", "Balanced", "Right");
            //this.feature4.Refresh(
            //    GetPercentage(result_.binary_direction_backward_),
            //    GetPercentage(result_.binary_direction_forward_),
            //    1 - (GetPercentage(result_.binary_direction_backward_) + GetPercentage(result_.binary_direction_forward_)),
            //    "Direction", "Backward", "Forward", "Unchanged");
            //this.feature5.Refresh(0.4, 0.3, 0.3, "Global Movement", "Too much", "Average", "Too little");
		}


        /// <summary>
        /// Display the final scores
        /// </summary>
        private void DisplayScores()
        {
            double width = 0;
            for (int i = 1; i < this.grdScores.ColumnDefinitions.Count; i++)
            {
                width += this.grdScores.ColumnDefinitions[i].ActualWidth;
            }
            this.rtgOverall.Width = width * result_.score_overall_ / 10;
            this.rtgContraction.Width = width * result_.score_contraction_ / 10;
            this.rtgDirection.Width = width * result_.score_direction_ / 10;
            this.rtgMovement.Width = width * result_.score_displacement_ / 10;
            this.rtgEnergy.Width = width * result_.score_energy_ / 10;
            this.rtgImpulse.Width = width * result_.score_impulse_ / 10;
            this.rtgStability.Width = width * result_.score_stability_ / 10;
        }


        void timer_trackbar__Tick(object sender, EventArgs e)
        {
            DisplayScores();
            this.feature1.UpdateMediaPosition(this.media.MediaPosition, this.media.MediaDuration);
            this.feature2.UpdateMediaPosition(this.media.MediaPosition, this.media.MediaDuration);
            this.feature3.UpdateMediaPosition(this.media.MediaPosition, this.media.MediaDuration);
        }
	}
}