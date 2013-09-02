namespace EAViewTestCSharp
{
    partial class MainWindow
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.eaViewGlobeControl1 = new EAViewEngine.EAViewGlobeControl();
            this.SuspendLayout();
            // 
            // eaViewGlobeControl1
            // 
            this.eaViewGlobeControl1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.eaViewGlobeControl1.ForeColor = System.Drawing.SystemColors.WindowFrame;
            this.eaViewGlobeControl1.Location = new System.Drawing.Point(0, 0);
            this.eaViewGlobeControl1.Name = "eaViewGlobeControl1";
            this.eaViewGlobeControl1.Size = new System.Drawing.Size(661, 492);
            this.eaViewGlobeControl1.TabIndex = 0;
            // 
            // MainWindow
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(661, 492);
            this.Controls.Add(this.eaViewGlobeControl1);
            this.Name = "MainWindow";
            this.Text = "MainWindow";
            this.ResumeLayout(false);

        }

        #endregion

        private EAViewEngine.EAViewGlobeControl eaViewGlobeControl1;

    }
}

