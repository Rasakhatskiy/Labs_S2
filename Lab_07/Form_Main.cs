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


        public Form_Main()
        {
            InitializeComponent();
        }

        private void Form_Main_Load(object sender, EventArgs e)
        {
            textBox_path.GotFocus += new EventHandler(TextBox_Focus);
            textBox_path.LostFocus += new EventHandler(TextBox_LostFocus);
            TextBox_LostFocus(textBox_path, null);


        }

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
    }
}
