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
            this.axEAViewGlobe1 = new EAViewEngine.AxEAViewGlobe();
            this.SuspendLayout();
            // 
            // axEAViewGlobe1
            // 
            this.axEAViewGlobe1.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
                        | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.axEAViewGlobe1.Location = new System.Drawing.Point(13, 13);
            this.axEAViewGlobe1.Name = "axEAViewGlobe1";
            this.axEAViewGlobe1.Size = new System.Drawing.Size(420, 294);
            this.axEAViewGlobe1.TabIndex = 0;
            // 
            // MainWindow
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(445, 319);
            this.Controls.Add(this.axEAViewGlobe1);
            this.Name = "MainWindow";
            this.Text = "MainWindow";
            this.ResumeLayout(false);

        }

        #endregion

        private EAViewEngine.AxEAViewGlobe axEAViewGlobe1;
    }
}

