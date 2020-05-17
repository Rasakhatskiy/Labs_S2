using System;
using System.Diagnostics;
using System.Windows.Forms;

namespace MyTemplateForms
{
    public partial class Form_About : Form
    {
        public string ProgramName { get; private set; }

        string Email =    @"saharok.maks@gmail.ua";
        string HomePage = @"https://bit.ly/2pK1421";


        public Form_About(string programName)
        {
            InitializeComponent();
            ProgramName = programName;
            System.Reflection.Assembly assembly = System.Reflection.Assembly.GetExecutingAssembly();
            FileVersionInfo fvi = FileVersionInfo.GetVersionInfo(assembly.Location);
            string version = fvi.FileVersion;
            version = version.Remove(version.Length - 1);
            version = version.Remove(version.Length - 1);
            labelVersion.Text = version;

            linkEMail.Text = Email;
            linkHome.Text = HomePage;

        }
        private void linkSite_LinkClicked(object sender, LinkLabelLinkClickedEventArgs e)
        {
            linkHome.LinkVisited = true;
            System.Diagnostics.Process.Start(linkHome.Text);
        }
        private void linkEMail_LinkClicked_1(object sender, LinkLabelLinkClickedEventArgs e)
        {
            linkEMail.LinkVisited = true;
            System.Diagnostics.Process.Start("mailto:" + linkEMail.Text);
        }
        private void linkLabel1_LinkClicked(object sender, LinkLabelLinkClickedEventArgs e)
        {
        }
        private void buttonAboutOk_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void Form_About_Load(object sender, EventArgs e)
        {
            label_program_name.Text = ProgramName;
        }

        private void button_CopyEmail_Click(object sender, EventArgs e)
        {
            Clipboard.SetText(Email);
        }
    }
}
