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
using System.Windows.Shapes;

namespace GUI
{
    public enum ContentInMainForm
    {
        Home,
        Practice,
        Practice_FullScreen,
        Result
    }
    
	/// <summary>
	/// Interaction logic for frmMain.xaml
	/// </summary>
	public partial class frmMain : Window
	{
		public frmMain()
		{
			this.InitializeComponent();


            RequiredInterface.GUIFeatureInterface feature_interface = new RequiredInterface.GUIFeatureInterface();
            //feature_interface.GenerateFeaturesFromONI("D:\\Data for Development\\ONI\\131.oni", "D:\\");
            feature_interface.PerformFeatureAnalysis("C:\\");
            feature_interface.SaveResultData("D:\\");
            
            //double[] scores = feature_interface.GetScores();


			// Insert code required on object creation below this point.
            SwitchWindow(ContentInMainForm.Home);
		}

        public void SwitchWindow(ContentInMainForm content)
        {
            this.LayoutRoot.Children.Clear();
            if (content == ContentInMainForm.Home)
            {
                ucHome home = new ucHome();
                this.LayoutRoot.Children.Add(home);
            }
            if (content == ContentInMainForm.Practice)
            {
                ucPractice practice = new ucPractice();
                this.LayoutRoot.Children.Add(practice);
            }
            if (content == ContentInMainForm.Practice_FullScreen)
            {
                ucPractice_FullScreen practice_full = new ucPractice_FullScreen();
                this.LayoutRoot.Children.Add(practice_full);
            }
            if (content == ContentInMainForm.Result)
            {
                ucBriefResults result_brief = new ucBriefResults();
                this.LayoutRoot.Children.Add(result_brief);
            }
        }
	}
}