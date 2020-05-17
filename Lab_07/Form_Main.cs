using Microsoft.WindowsAPICodePack.Dialogs;
using MyTemplateForms;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Lab_07
{
    public partial class Form_Main : Form
    {
        const string helpString = "Select/Enter/Drag (from admin explorer)";

        List<DataWork.DiskInfo> DiskInfoList = new List<DataWork.DiskInfo>();
        DataTable ItemsComboboxDisks = new DataTable();

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
            if(textBox.Text == helpString)
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
                textBox.Text = helpString;
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
                    $"Disk drive {res.id}\n{res.model}\n{res.size} GB",
                    $"Disk drive {res.id}  {res.model}  {res.size} GB",
                    $"Disk drive {res.id}\n{res.model}\n{res.size} GB"
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
    }
}
