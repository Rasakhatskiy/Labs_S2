using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab_07
{
    class Parameter
    {

        public BinaryWriter BinaryWriter { get; set; }

        public int CameraNumber { get; set; }

        public int FirstTimeInt { get; set; }

        public int LastTimeInt { get; set; }

        public DateTime LastDateTime { get; set; }

        public int Position { get; set; }

        public byte[] Buffer { get; set; }

        public string Path { get; set; }

        public int Size { get; set; }


        private const int BUFFER_SIZE = 8 * 1024 * 1024;


        public Parameter(string tempName, int cameraNum, int dateTime)
        {
            Position = 0;
            Size = 0;
            CameraNumber = cameraNum;
            FirstTimeInt = dateTime;
            LastTimeInt = dateTime;
            LastDateTime = Converter.Convert_DHFS_ToDateTime(dateTime);
            Path = tempName + cameraNum.ToString();
            BinaryWriter = new BinaryWriter(File.OpenWrite(Path));
            Buffer = new byte[BUFFER_SIZE];
        }

        public void Close()
        {
            BinaryWriter.Write(Buffer, 0, Position);
            BinaryWriter.Close();
        }

        public void Open(int time)
        {
            if (BinaryWriter != null) BinaryWriter.Dispose();
            BinaryWriter = new BinaryWriter(File.OpenWrite(Path));
            Position = 0;
            Size = 0;
            FirstTimeInt = time;
            LastTimeInt = time;
        }
    }
}
