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
	/// Interaction logic for ucHome.xaml
	/// </summary>
	public partial class ucHome : UserControl
	{
		public ucHome()
		{
			this.InitializeComponent();
		}

        private void btnPractice_Click(object sender, RoutedEventArgs e)
        {
            frmMain main_form = (frmMain)((Grid)this.Parent).Parent;
            main_form.SwitchWindow(ContentInMainForm.Practice_FullScreen);
        }
	}
}