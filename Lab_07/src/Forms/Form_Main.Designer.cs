namespace Lab_07
{
    partial class Form_Main
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
            this.components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Form_Main));
            this.textBox_path = new System.Windows.Forms.TextBox();
            this.label2 = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.button_browse = new System.Windows.Forms.Button();
            this.button_start = new System.Windows.Forms.Button();
            this.button_refresh = new System.Windows.Forms.Button();
            this.progressBar = new System.Windows.Forms.ProgressBar();
            this.label_progress = new System.Windows.Forms.Label();
            this.timer_progress = new System.Windows.Forms.Timer(this.components);
            this.comboBox_disks = new MyTemplateForms.ComboxBoxEx();
            this.SuspendLayout();
            // 
            // textBox_path
            // 
            this.textBox_path.AllowDrop = true;
            this.textBox_path.Location = new System.Drawing.Point(118, 55);
            this.textBox_path.Name = "textBox_path";
            this.textBox_path.Size = new System.Drawing.Size(241, 20);
            this.textBox_path.TabIndex = 3;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(15, 58);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(97, 13);
            this.label2.TabIndex = 2;
            this.label2.Text = "Select result folder:";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(15, 16);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(66, 13);
            this.label1.TabIndex = 1;
            this.label1.Text = "Select drive:";
            // 
            // button_browse
            // 
            this.button_browse.BackColor = System.Drawing.Color.White;
            this.button_browse.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.button_browse.Location = new System.Drawing.Point(379, 54);
            this.button_browse.Name = "button_browse";
            this.button_browse.Size = new System.Drawing.Size(75, 21);
            this.button_browse.TabIndex = 4;
            this.button_browse.Text = "Browse";
            this.button_browse.UseVisualStyleBackColor = false;
            this.button_browse.Click += new System.EventHandler(this.Button_browse_Click);
            // 
            // button_start
            // 
            this.button_start.BackColor = System.Drawing.Color.White;
            this.button_start.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.button_start.Location = new System.Drawing.Point(379, 97);
            this.button_start.Name = "button_start";
            this.button_start.Size = new System.Drawing.Size(75, 21);
            this.button_start.TabIndex = 5;
            this.button_start.Text = "Start";
            this.button_start.UseVisualStyleBackColor = false;
            this.button_start.Click += new System.EventHandler(this.button_start_Click);
            // 
            // button_refresh
            // 
            this.button_refresh.BackColor = System.Drawing.Color.White;
            this.button_refresh.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.button_refresh.Location = new System.Drawing.Point(379, 12);
            this.button_refresh.Name = "button_refresh";
            this.button_refresh.Size = new System.Drawing.Size(75, 21);
            this.button_refresh.TabIndex = 6;
            this.button_refresh.Text = "Refresh";
            this.button_refresh.UseVisualStyleBackColor = false;
            this.button_refresh.Click += new System.EventHandler(this.Button_refresh_Click);
            // 
            // progressBar
            // 
            this.progressBar.Location = new System.Drawing.Point(118, 97);
            this.progressBar.Name = "progressBar";
            this.progressBar.Size = new System.Drawing.Size(205, 21);
            this.progressBar.TabIndex = 7;
            this.progressBar.Visible = false;
            // 
            // label_progress
            // 
            this.label_progress.AutoSize = true;
            this.label_progress.Location = new System.Drawing.Point(328, 101);
            this.label_progress.Name = "label_progress";
            this.label_progress.Size = new System.Drawing.Size(33, 13);
            this.label_progress.TabIndex = 8;
            this.label_progress.Text = "100%";
            this.label_progress.Visible = false;
            // 
            // timer_progress
            // 
            this.timer_progress.Interval = 1000;
            this.timer_progress.Tick += new System.EventHandler(this.timer_progress_Tick);
            // 
            // comboBox_disks
            // 
            this.comboBox_disks.FormattingEnabled = true;
            this.comboBox_disks.Location = new System.Drawing.Point(118, 12);
            this.comboBox_disks.Name = "comboBox_disks";
            this.comboBox_disks.Size = new System.Drawing.Size(241, 21);
            this.comboBox_disks.TabIndex = 0;
            this.comboBox_disks.DropDown += new System.EventHandler(this.ComboBox_disks_DropDown);
            this.comboBox_disks.SelectedIndexChanged += new System.EventHandler(this.ComboBox_disks_SelectedIndexChanged);
            this.comboBox_disks.DropDownClosed += new System.EventHandler(this.ComboBox_disks_DropDownClosed);
            // 
            // Form_Main
            // 
            this.AllowDrop = true;
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(245)))), ((int)(((byte)(247)))), ((int)(((byte)(249)))));
            this.ClientSize = new System.Drawing.Size(465, 130);
            this.Controls.Add(this.label_progress);
            this.Controls.Add(this.progressBar);
            this.Controls.Add(this.button_refresh);
            this.Controls.Add(this.button_start);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.button_browse);
            this.Controls.Add(this.comboBox_disks);
            this.Controls.Add(this.textBox_path);
            this.Controls.Add(this.label2);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MaximizeBox = false;
            this.Name = "Form_Main";
            this.Text = "Video Recovery";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.Form_Main_FormClosing);
            this.Load += new System.EventHandler(this.Form_Main_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion
        private System.Windows.Forms.TextBox textBox_path;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label1;
        private MyTemplateForms.ComboxBoxEx comboBox_disks;
        private System.Windows.Forms.Button button_browse;
        private System.Windows.Forms.Button button_start;
        private System.Windows.Forms.Button button_refresh;
        private System.Windows.Forms.ProgressBar progressBar;
        private System.Windows.Forms.Label label_progress;
        private System.Windows.Forms.Timer timer_progress;
    }
}