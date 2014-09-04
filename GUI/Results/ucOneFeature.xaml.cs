//
//  Smart Tutor v1.0
//	GUI
//  The segments to display result of one feature
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

namespace GUI
{
	/// <summary>
	/// Interaction logic for ucOneFeature.xaml
	/// </summary>
	public partial class ucOneFeature : UserControl
    {
        // Only show time-line when clicked on the pie chart
        private bool is_showing_timeline_ = false;

        // The comment displayed above the time-line
        private string comment_1_, comment_2_, comment_3_;

        // The appearance of 3 codewords
        private List<bool> binary_1_ = new List<bool>();
        private List<bool> binary_2_ = new List<bool>();
        private List<bool> binary_3_ = new List<bool>();

        // Generated from binary lists, support visualisation
        private List<int> id_start_ = new List<int>();
        private List<int> id_end_ = new List<int>();
        private List<Rectangle> timeline_segments_ = new List<Rectangle>();
        

		public ucOneFeature()
		{
			this.InitializeComponent();
		}


        /// <summary>
        /// Call from result form, input data for the control
        /// </summary>
        public void InputData(
            string title_main, 
            string title_1, string title_2, string title_3,
            string comment_1, string comment_2, string comment_3,
            List<bool> binary1, List<bool> binary2, List<bool> binary3)
        {
            comment_1_ = comment_1;
            comment_2_ = comment_2;
            comment_3_ = comment_3;

            binary_1_ = binary1;
            binary_2_ = binary2;
            binary_3_ = binary3;

            this.lblMain.Content = title_main;
            this.lbl1.Content = title_1;
            this.lbl2.Content = title_2;
            this.lbl3.Content = title_3;

            this.arc1.StartAngle = 0;
            this.arc1.EndAngle = 360 * GetPercentageofBinary(binary_1_);
            this.arc2.StartAngle = this.arc1.EndAngle;
            this.arc2.EndAngle = this.arc2.StartAngle + 360 * GetPercentageofBinary(binary_2_);
            this.arc3.StartAngle = this.arc2.EndAngle;
            this.arc3.EndAngle = 360;
        }


        /// <summary>
        /// Run the time-line based on media's current position
        /// </summary>
        public void UpdateMediaPosition(double media_position_in_ms, double media_duration)
        {
            if (this.is_showing_timeline_)
            {
                Thickness margin = new Thickness();
                margin.Left = this.grdTimeline.ActualWidth * (media_position_in_ms / media_duration);
                this.line_media_position.Margin = margin;
            }
        }


        /// <summary>
        /// private, Update the time-line that represent codewords 
        /// Called when click on codeword of pie chart
        /// </summary>
        private void DisplayTimeLine_n_Comment(List<bool> binary_, string comment)
        {
            this.is_showing_timeline_ = true;
            this.lblComment.Content = comment;

            ///////////////////////////////////////////////////////////////////////////////////
            // Clean up
            List<UIElement> to_delete = new List<UIElement>();
            foreach(UIElement child in this.grdTimeline.Children)
            {
                if (child.Uid == "segment")
                    to_delete.Add(child);
            }
            foreach(UIElement child in to_delete)
            {
                this.grdTimeline.Children.Remove(child);
            }
            timeline_segments_.Clear();
            id_start_.Clear();
            id_end_.Clear();

            ///////////////////////////////////////////////////////////////////////////////////
            // Separate the binary list into separated segments
            if (binary_[0])
                id_start_.Add(0);
            for (int i = 0; i < binary_.Count - 1; i++)
            {
                if (!binary_[i] && binary_[i + 1])
                {
                    id_start_.Add(i + 1);
                }
                if (binary_[i] && !binary_[i + 1])
                {
                    id_end_.Add(i);
                }
            }
            if (binary_[binary_.Count - 1])
                id_end_.Add(binary_.Count - 1);
            
            ////////////////////////////////////////////////////////////////////////////////////
            // Draw the bars
            for (int i = 0; i < id_start_.Count; i++)
            {
                Rectangle bar = new Rectangle();
                bar.HorizontalAlignment = System.Windows.HorizontalAlignment.Left;
                bar.VerticalAlignment = System.Windows.VerticalAlignment.Center;
                bar.Height = 15;
                bar.Width = this.grdTimeline.ActualWidth * (id_end_[i] - id_start_[i]) / binary_.Count;
                Thickness margin = bar.Margin;
                margin.Left = this.grdTimeline.ActualWidth * id_start_[i] / binary_.Count;
                bar.Margin = margin;
                SolidColorBrush brush = new SolidColorBrush(Color.FromRgb(100, 100, 100));
                bar.Fill = brush;
                bar.MouseDown += bar_MouseDown;
                bar.Tag = i;
                bar.Uid = "segment";

                timeline_segments_.Add(bar);
            }
            
            for (int i = 0; i < timeline_segments_.Count; i++)
            {
                this.grdTimeline.Children.Add(timeline_segments_[i]);
            }
        }


        /// <summary>
        /// Get percentage of appearance of one codeword via a binary list
        /// </summary>
        private double GetPercentageofBinary(List<bool> binary)
        {
            int count = 0;
            for (int i = 0; i < binary.Count; i++)
            {
                if (binary[i]) count++;
            }
            return (double)count / binary.Count;
        }


        #region Interaction with the form
        //-----------------------------------------------------------------------------------------------------------------------

        void bar_MouseDown(object sender, MouseButtonEventArgs e)
        {
            // Get the id back from the chosen bar
            int id = (int)((Rectangle)sender).Tag;
            int segment_start_id = id_start_[id];
            int segment_end_id = id_end_[id];

            // Adjust the start and end position of the video
            // Search for the media player user control

        }

        private void arc1_MouseDown(object sender, MouseButtonEventArgs e)
        {
            DisplayTimeLine_n_Comment(binary_1_, comment_1_);
        }

        private void arc2_MouseDown(object sender, MouseButtonEventArgs e)
        {
            DisplayTimeLine_n_Comment(binary_2_, comment_2_);
        }

        private void arc3_MouseDown(object sender, MouseButtonEventArgs e)
        {
            DisplayTimeLine_n_Comment(binary_3_, comment_3_);
        }

        private void lbl1_MouseDown(object sender, MouseButtonEventArgs e)
        {
            arc1_MouseDown(sender, e);
        }

        private void lbl2_MouseDown(object sender, MouseButtonEventArgs e)
        {
            arc2_MouseDown(sender, e);
        }

        private void lbl3_MouseDown(object sender, MouseButtonEventArgs e)
        {
            arc3_MouseDown(sender, e);
        }

        //-----------------------------------------------------------------------------------------------------------------------
        #endregion
    }
}