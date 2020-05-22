using System;
using System.Windows.Forms;
using System.Runtime.InteropServices;
using System.Collections.Generic;
using System.Data;
using System.Drawing;

namespace MyTemplateForms
{
    public partial class ComboxBoxEx : ComboBox
    {
        [DllImport("user32.dll")]
        [return: MarshalAs(UnmanagedType.Bool)]
        public static extern bool GetWindowRect(IntPtr hwnd, out RECT lpRect);

        [DllImport("user32.dll", SetLastError = true)]
        [return: MarshalAs(UnmanagedType.Bool)]
        private static extern bool SetWindowPos(IntPtr hWnd, IntPtr hWndInsertAfter, int x, int y, int cx, int cy, uint uFlags);

        [StructLayout(LayoutKind.Sequential)]
        public struct RECT
        {
            public int Left;        // x position of upper-left corner 
            public int Top;         // y position of upper-left corner 
            public int Right;       // x position of lower-right corner 
            public int Bottom;      // y position of lower-right corner 
        }

        public const int SWP_NOZORDER = 0x0004;
        public const int SWP_NOACTIVATE = 0x0010;
        public const int SWP_FRAMECHANGED = 0x0020;
        public const int SWP_NOOWNERZORDER = 0x0200;

        public const int WM_CTLCOLORLISTBOX = 0x0134;

        private int _hwndDropDown = 0;

        public ComboxBoxEx()
        {
            DrawItem += new DrawItemEventHandler(comboBox2_DrawItem);
            MeasureItem += new MeasureItemEventHandler(comboBox2_MeasureItem);
            SelectedIndexChanged += new EventHandler(comboBox2_SelectedIndexChanged);
        }
        

        internal List<int> ItemHeights = new List<int>();

        protected override void WndProc(ref Message m)
        {
            if (m.Msg == WM_CTLCOLORLISTBOX)
            {
                if (_hwndDropDown == 0)
                {
                    _hwndDropDown = m.LParam.ToInt32();

                    RECT r;
                    GetWindowRect((IntPtr)_hwndDropDown, out r);

                    int newHeight = 0;
                    int n = (Items.Count > MaxDropDownItems) ? MaxDropDownItems : Items.Count;
                    for (int i = 0; i < n; i++)
                    {
                        newHeight += ItemHeights[i];
                    }
                    newHeight += 2; //to stop scrollbars showing

                    SetWindowPos((IntPtr)_hwndDropDown, IntPtr.Zero,
                        r.Left,
                                 r.Top,
                                 DropDownWidth,
                                 newHeight,
                                 SWP_FRAMECHANGED |
                                     SWP_NOACTIVATE |
                                     SWP_NOZORDER |
                                     SWP_NOOWNERZORDER);
                }
            }

            base.WndProc(ref m);
        }

        protected override void OnDropDownClosed(EventArgs e)
        {
            _hwndDropDown = 0;
            base.OnDropDownClosed(e);

           
        }

        private void comboBox2_MeasureItem(object sender, MeasureItemEventArgs e)
        {
            ComboxBoxEx comboBoxSender = (ComboxBoxEx)sender;

           

            DataRowView item = (DataRowView)comboBoxSender.Items[e.Index];
            string txt = item["fullInfo"].ToString();

            int height = Convert.ToInt32(e.Graphics.MeasureString(txt, comboBoxSender.Font).Height);

            e.ItemHeight = height + 4;
            if(e.Index == 0)
            {
                e.ItemHeight = 0;
            }
            e.ItemWidth = comboBoxSender.DropDownWidth;

            comboBoxSender.ItemHeights.Add(e.ItemHeight);
        }

        private void comboBox2_DrawItem(object sender, DrawItemEventArgs e)
        {
            ComboxBoxEx comboBoxSender = (ComboxBoxEx)sender;

            //for (int index = 0; index < comboBoxSender.Items.Count; index++)
            //{
            //    if (index != 0)
            //    {
            //        ((DataRowView)comboBoxSender.Items[index])["fullInfo"] = ((DataRowView)comboBoxSender.Items[index])["id"];
            //    }
            //}


            DataRowView item = (DataRowView)comboBoxSender.Items[e.Index];
            string txt = item["fullInfo"].ToString();

            e.DrawBackground();
            e.Graphics.DrawString(txt, comboBoxSender.Font, System.Drawing.Brushes.Black, new RectangleF(e.Bounds.X + 2, e.Bounds.Y + 2, e.Bounds.Width, e.Bounds.Height));

            //e.Graphics.DrawLine(new Pen(Color.LightGray), e.Bounds.X, e.Bounds.Top + e.Bounds.Height - 1, e.Bounds.Width, e.Bounds.Top + e.Bounds.Height - 1);
            //e.DrawFocusRectangle();
        }

        private void comboBox2_SelectedIndexChanged(object sender, EventArgs e)
        {
            ComboxBoxEx senderComboBox = (ComboxBoxEx)sender;
            if (senderComboBox.SelectedItem == null) return;

            DataRowView item = (DataRowView)senderComboBox.SelectedItem;
        }
    }
}