using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using EAViewEngine;


namespace EAViewTestCSharp
{
    public partial class MainWindow : Form
    {
        EAViewGlobe ea;
        public MainWindow()
        {
            InitializeComponent();
            ea=this.eaViewGlobeControl1.Object as EAViewGlobe;
        }

        private void loadModelToolStripMenuItem_Click(object sender, EventArgs e)
        {
            OpenFileDialog oDlg = new OpenFileDialog();
            oDlg.Multiselect = false;
            if (oDlg.ShowDialog()==DialogResult.OK)
            {
                ea.LoadOSGModel(oDlg.FileName);
            }
            
        }
    }
}
