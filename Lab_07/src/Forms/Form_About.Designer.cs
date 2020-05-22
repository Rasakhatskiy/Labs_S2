namespace MyTemplateForms
{
    partial class Form_About
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Form_About));
            this.button_OK = new System.Windows.Forms.Button();
            this.label3 = new System.Windows.Forms.Label();
            this.labelVersion = new System.Windows.Forms.Label();
            this.label_program_name = new System.Windows.Forms.Label();
            this.logoPictureBox = new System.Windows.Forms.PictureBox();
            this.linkEMail = new System.Windows.Forms.LinkLabel();
            this.linkHome = new System.Windows.Forms.LinkLabel();
            this.button_CopyEmail = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.logoPictureBox)).BeginInit();
            this.SuspendLayout();
            // 
            // button_OK
            // 
            this.button_OK.Cursor = System.Windows.Forms.Cursors.Hand;
            this.button_OK.Font = new System.Drawing.Font("Tahoma", 8F);
            this.button_OK.Location = new System.Drawing.Point(383, 202);
            this.button_OK.Name = "button_OK";
            this.button_OK.Size = new System.Drawing.Size(93, 20);
            this.button_OK.TabIndex = 46;
            this.button_OK.Text = "OK";
            this.button_OK.Click += new System.EventHandler(this.buttonAboutOk_Click);
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.label3.Location = new System.Drawing.Point(9, 202);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(278, 16);
            this.label3.TabIndex = 45;
            this.label3.Text = "Copyright© 2013-2020, Maksym Rasakhatskyi";
            // 
            // labelVersion
            // 
            this.labelVersion.AutoSize = true;
            this.labelVersion.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.labelVersion.Location = new System.Drawing.Point(209, 56);
            this.labelVersion.Name = "labelVersion";
            this.labelVersion.Size = new System.Drawing.Size(84, 16);
            this.labelVersion.TabIndex = 44;
            this.labelVersion.Text = "Version 0.0.0";
            // 
            // label_program_name
            // 
            this.label_program_name.AutoSize = true;
            this.label_program_name.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.label_program_name.Location = new System.Drawing.Point(209, 26);
            this.label_program_name.Name = "label_program_name";
            this.label_program_name.Size = new System.Drawing.Size(112, 16);
            this.label_program_name.TabIndex = 43;
            this.label_program_name.Text = "Program Name";
            // 
            // logoPictureBox
            // 
            this.logoPictureBox.Image = ((System.Drawing.Image)(resources.GetObject("logoPictureBox.Image")));
            this.logoPictureBox.Location = new System.Drawing.Point(12, 12);
            this.logoPictureBox.Name = "logoPictureBox";
            this.logoPictureBox.Size = new System.Drawing.Size(180, 180);
            this.logoPictureBox.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage;
            this.logoPictureBox.TabIndex = 39;
            this.logoPictureBox.TabStop = false;
            // 
            // linkEMail
            // 
            this.linkEMail.AutoSize = true;
            this.linkEMail.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.linkEMail.Location = new System.Drawing.Point(209, 86);
            this.linkEMail.Name = "linkEMail";
            this.linkEMail.Size = new System.Drawing.Size(27, 16);
            this.linkEMail.TabIndex = 40;
            this.linkEMail.TabStop = true;
            this.linkEMail.Text = "oof";
            this.linkEMail.LinkClicked += new System.Windows.Forms.LinkLabelLinkClickedEventHandler(this.linkEMail_LinkClicked_1);
            // 
            // linkHome
            // 
            this.linkHome.AutoSize = true;
            this.linkHome.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.linkHome.Location = new System.Drawing.Point(209, 115);
            this.linkHome.Name = "linkHome";
            this.linkHome.Size = new System.Drawing.Size(17, 16);
            this.linkHome.TabIndex = 41;
            this.linkHome.TabStop = true;
            this.linkHome.Text = "E";
            this.linkHome.LinkClicked += new System.Windows.Forms.LinkLabelLinkClickedEventHandler(this.linkSite_LinkClicked);
            // 
            // button_CopyEmail
            // 
            this.button_CopyEmail.Cursor = System.Windows.Forms.Cursors.Hand;
            this.button_CopyEmail.Font = new System.Drawing.Font("Tahoma", 8F);
            this.button_CopyEmail.Location = new System.Drawing.Point(383, 86);
            this.button_CopyEmail.Name = "button_CopyEmail";
            this.button_CopyEmail.Size = new System.Drawing.Size(93, 20);
            this.button_CopyEmail.TabIndex = 47;
            this.button_CopyEmail.Text = "Copy Email";
            this.button_CopyEmail.Click += new System.EventHandler(this.button_CopyEmail_Click);
            // 
            // Form_About
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(487, 234);
            this.Controls.Add(this.button_CopyEmail);
            this.Controls.Add(this.button_OK);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.labelVersion);
            this.Controls.Add(this.label_program_name);
            this.Controls.Add(this.logoPictureBox);
            this.Controls.Add(this.linkEMail);
            this.Controls.Add(this.linkHome);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.MaximizeBox = false;
            this.Name = "Form_About";
            this.ShowIcon = false;
            this.ShowInTaskbar = false;
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterParent;
            this.Text = "About";
            this.Load += new System.EventHandler(this.Form_About_Load);
            ((System.ComponentModel.ISupportInitialize)(this.logoPictureBox)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button button_OK;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label labelVersion;
        private System.Windows.Forms.Label label_program_name;
        private System.Windows.Forms.PictureBox logoPictureBox;
        private System.Windows.Forms.LinkLabel linkEMail;
        private System.Windows.Forms.LinkLabel linkHome;
        private System.Windows.Forms.Button button_CopyEmail;
    }
}