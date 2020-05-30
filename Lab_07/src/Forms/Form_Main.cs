using Microsoft.WindowsAPICodePack.Dialogs;
using MyTemplateForms;
using System;
using System.Collections.Generic;
using System.Data;
using System.Drawing;
using System.IO;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Lab_07
{
    public partial class Form_Main : Form
    {


        List<DataWork.DiskInfo> DiskInfoList = new List<DataWork.DiskInfo>();
        DataTable ItemsComboboxDisks = new DataTable();
        Extractor myExtractor;
        bool IsRunning = false;
        Task MainTask;


        public Form_Main()
        {
            InitializeComponent();
            InitializeComboBox();
        }

        private void Form_Main_Load(object sender, EventArgs e)
        {
            textBox_path.GotFocus += new EventHandler(TextBox_Focus);
            textBox_path.LostFocus += new EventHandler(TextBox_LostFocus);
            TextBox_LostFocus(textBox_path, null);

        }

        #region TextBox Path

        protected void TextBox_Focus(Object sender, EventArgs e)
        {
            var textBox = sender as TextBox;
            if(textBox.Text == String_help)
            {
                textBox.Text = "";
                textBox.ForeColor = Color.Black;
            }
        }

        private void TextBox_LostFocus(object sender, EventArgs e)
        {
            var textBox = sender as TextBox;
            if (textBox.Text == "")
            {
                textBox.Text = String_help;
                textBox.ForeColor = Color.Gray;
            }
        }

        #endregion

        #region ComboBox Disks

        private void InitializeComboBox()
        {
            ItemsComboboxDisks.Columns.AddRange(
                new DataColumn[] {
                    new DataColumn("id"),
                    new DataColumn("display"),
                    new DataColumn("fullInfo") });

            comboBox_disks.DrawMode = DrawMode.OwnerDrawVariable;

            comboBox_disks.ValueMember = "id";
            comboBox_disks.DisplayMember = "display";
            comboBox_disks.BringToFront();

            Button_refresh_Click(null, null);
        }

        private void Button_refresh_Click(object sender, EventArgs e)
        {
            DiskInfoList = DataWork.DiskInfo.GetDiskInfoList();
            ItemsComboboxDisks = new DataTable();

            ItemsComboboxDisks.Columns.AddRange(
                new DataColumn[] {
                    new DataColumn("id"),
                    new DataColumn("display"),
                    new DataColumn("fullInfo") });

            ItemsComboboxDisks.Rows.Add(new object[] { "", "", "" });

            foreach (var res in DiskInfoList)
            {
                ItemsComboboxDisks.Rows.Add(new object[]
                {
                    $"Disk drive {res.ID}\n{res.Model}\n{res.Size} GB",
                    $"Disk drive {res.ID}  {res.Model}  {res.Size} GB",
                    $"Disk drive {res.ID}\n{res.Model}\n{res.Size} GB"
                });
            }

            comboBox_disks.DataSource = new BindingSource(ItemsComboboxDisks, null);
            comboBox_disks.DisplayMember = "id";
        }

        private void ComboBox_disks_SelectedIndexChanged(object sender, EventArgs e)
        {
            var comboBox = sender as ComboxBoxEx;
            if (comboBox_disks.SelectedIndex <= 0 || 
                comboBox.SelectedIndex > DiskInfoList.Count)
                return;
            button_start.Enabled = true;
        }

        private void ComboBox_disks_DropDownClosed(object sender, EventArgs e)
        {
            var comboBox = sender as ComboxBoxEx;
            var index = comboBox.SelectedIndex;
            if (index > 0)
                ((DataRowView)comboBox_disks.Items[index])["fullInfo"] = 
                    ((DataRowView)comboBox_disks.Items[index])["display"];
        }

        private void ComboBox_disks_DropDown(object sender, EventArgs e)
        {
            var comboBox = sender as ComboxBoxEx;
            for (int index = 1; index < comboBox.Items.Count; ++index)
                ((DataRowView)comboBox.Items[index])["fullInfo"] = 
                    ((DataRowView)comboBox.Items[index])["id"];
        }

        #endregion

        private void Button_browse_Click(object sender, EventArgs e)
        {
            CommonOpenFileDialog dialog = new CommonOpenFileDialog()
            {
                InitialDirectory = Environment.GetFolderPath(Environment.SpecialFolder.MyComputer),
                IsFolderPicker = true
            };

            if (dialog.ShowDialog() == CommonFileDialogResult.Ok)
            {
                textBox_path.Text = dialog.FileName;
                textBox_path.ForeColor = Color.Black;
            }
        }

        private void button_start_Click(object sender, EventArgs e)
        {
            if (comboBox_disks.SelectedIndex < 1)
            {
                MessageBox.Show(
                    String_incorrectInput, 
                    String_noDiskSelected, 
                    MessageBoxButtons.OK, 
                    MessageBoxIcon.Warning);
                return;
            }

            if (!Directory.Exists(textBox_path.Text))
            {
                MessageBox.Show(
                    String_incorrectInput, 
                    String_incorrectPath, 
                    MessageBoxButtons.OK, 
                    MessageBoxIcon.Warning);
                return;
            }

            myExtractor = new Extractor(
                DiskInfoList[comboBox_disks.SelectedIndex - 1].ID, 
                textBox_path.Text, 
                0,
                DiskInfoList[comboBox_disks.SelectedIndex - 1].NumberOfSectors);

            SwitchControls(false);
            timer_progress.Start();
            IsRunning = true;
            MainTask = Task.Run(() =>
            {
                myExtractor.Start();
            });

            
        }

        private void timer_progress_Tick(object sender, EventArgs e)
        {
            if(myExtractor.IsCompleted)
            {
                timer_progress.Stop();
                MessageBox.Show("Operation completed", "Completed", MessageBoxButtons.OK, MessageBoxIcon.Asterisk);
                SwitchControls(true);
                IsRunning = false;
                return;
            }

            var progress =
                myExtractor.Progress >= 0 && myExtractor.Progress <= 100 ?
                myExtractor.Progress :
                100;

            progressBar.Value = progress;
            label_progress.Text = $"{progress}%";
        }

        private void SwitchControls(bool state)
        {
            comboBox_disks.Enabled = state;
            button_refresh.Enabled = state;
            textBox_path.Enabled = state;
            button_browse.Enabled = state;

            button_start.Visible = state;
            button_start.Enabled = state;

            progressBar.Visible = !state;
            label_progress.Visible = !state;

            label_progress.Text = "0%";
            progressBar.Value = 0;
        }

        private void Form_Main_FormClosing(object sender, FormClosingEventArgs e)
        {
            if (IsRunning && MessageBox.Show("Process is still running, are you usre you want to exit?", 
                                "Warning",
                                MessageBoxButtons.YesNo, 
                                MessageBoxIcon.Warning) == DialogResult.No)
            {
                e.Cancel = true;
            }
        }
    }
}
