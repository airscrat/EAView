﻿using System;
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
        public MainWindow()
        {
            InitializeComponent();
            EAViewGlobe ea=this.eaViewGlobeControl1.Object as EAViewGlobe;
        }
    }
}
