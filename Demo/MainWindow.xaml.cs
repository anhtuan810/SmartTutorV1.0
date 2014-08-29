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

namespace Demo
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        System.Windows.Threading.DispatcherTimer timer_ = new System.Windows.Threading.DispatcherTimer();
        bool media_playing_ = true;

        public MainWindow()
        {
            InitializeComponent();
            timer_.Tick += timer__Tick;
            timer_.Start();
        }

        void timer__Tick(object sender, EventArgs e)
        {
            if (this.media.NaturalDuration != Duration.Automatic)
            {
                double ratio = this.media.Position.TotalMilliseconds / this.media.NaturalDuration.TimeSpan.TotalMilliseconds;
                double width_frame = 1037;
                double width_new = ratio * width_frame;
                this.rtgTrack.Width = width_new;
            }
        }

        private void media_MouseDown(object sender, MouseButtonEventArgs e)
        {
            this.media.Play();
        }

        private void Label_MouseDown(object sender, MouseButtonEventArgs e)
        {
            this.media.Play();
        }

    }
}
