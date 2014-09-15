//
//  Smart Tutor v1.0
//	GUI
//
//  Created: 2014.09.15
//
//  Copyright (c) 2014 Anh Tuan Nguyen. All rights reserved.
//

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace GUI.Results
{
    /// <summary>
    /// Interaction logic for ucTimeLine.xaml
    /// </summary>
    public partial class ucTimeLine : UserControl
    {
        private List<bool> binary_;
        private string comment_;

        // Generated from binary lists, support visualisation
        private List<int> id_start_ = new List<int>();
        private List<int> id_end_ = new List<int>();
        private List<Rectangle> timeline_segments_ = new List<Rectangle>();


        public ucTimeLine()
        {
            InitializeComponent();
        }


        public void UpdateData(List<bool> binary_data, string comment)
        {
            binary_ = binary_data;
            comment_ = comment;
            this.lblComment.Content = comment;

            ///////////////////////////////////////////////////////////////////////////////////
            // Clean up
            List<UIElement> to_delete = new List<UIElement>();
            foreach (UIElement child in this.grdTimeline.Children)
            {
                if (child.Uid == "segment")
                    to_delete.Add(child);
            }
            foreach (UIElement child in to_delete)
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
        /// Run the time-line based on media's current position
        /// </summary>
        public void UpdateMediaPosition(double media_position_in_ms, double media_duration)
        {
            if (media_duration > 0)
            {
                Thickness margin = new Thickness();
                margin.Left = this.grdTimeline.ActualWidth * (media_position_in_ms / media_duration);
                this.line_media_position.Margin = margin;
            }
        }
    }
}
