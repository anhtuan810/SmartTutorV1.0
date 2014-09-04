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
	/// Interaction logic for ucTitle.xaml
	/// </summary>
	public partial class ucTitle : UserControl
	{
        private string title_;
        ContentInMainForm go_back_content_;

		public ucTitle()
		{
			this.InitializeComponent();
		}

        public void UpdateData(string title, ContentInMainForm go_back_content)
        {
            title_ = title;
            go_back_content_ = go_back_content;
            this.lblTitle.Content = title;
            this.btnBack.Click += btnBack_Click;
        }

        void btnBack_Click(object sender, RoutedEventArgs e)
        {
 	        frmMain frm = (frmMain)((Grid)((UserControl)((Grid)this.Parent).Parent).Parent).Parent;
            frm.SwitchWindow(go_back_content_);
        }

	}
}