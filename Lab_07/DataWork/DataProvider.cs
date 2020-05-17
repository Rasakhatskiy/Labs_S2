using System;
using System.Diagnostics;
using System.Threading;
using System.Threading.Tasks;

namespace DataWork
{
    class DataProvider
    {
        public bool IsOpen { get; set; }
        private byte[] BufferFirst;
        private byte[] BufferSecond;
        private byte[] BufferSector;

        public int Progress { get; private set; }
        public long SectorBegin { get; private set; }
        public long SectorEnd { get; private set; }
        public long PacksRead { get; private set; }
        public bool EndOfSource { get; private set; }
        public int BytesPerSector { get; private set; }

        public const int BUFFER_SIZE = 0x4000000;
        

        private Task TaskDataReceiver;

        private DataReceiver DataReceiver;
        private bool IsFirstActive = true;
        private long PacksInSource;
        //private int SectorsInSmall;
        private int SectorsInBuffer;
        private bool EndIsNear = false;

        double ProgressStep = 0;
        double TotalProgress = 0;

        public byte this[int index]
        {
            get => GetValue(index);
        }

        public DataProvider(int diskId)
        {
            IsOpen = true;
            DataReceiver = new DataWork.DataReceiver(diskId);
        }

        public DataProvider(string imagePath)
        {
            IsOpen = true;
            DataReceiver = new DataReceiver(imagePath);
        }
        
        public void Launch(long secBeg, long secEnd)
        {
            SectorBegin = secBeg;
            SectorEnd = secEnd;
            PacksInSource = (SectorEnd - SectorBegin) * DataReceiver.BytesPerSector / BUFFER_SIZE  + 1;
            BufferFirst = new byte[BUFFER_SIZE];
            BufferSecond = new byte[BUFFER_SIZE];
            BufferSector = new byte[DataReceiver.BytesPerSector];
            EndOfSource = false;
            TaskDataReceiver = Task.Run(() => { });
            //SectorsInSmall = (int)(BUFFER_LESS / DataReceiver.BytesPerSector);
            SectorsInBuffer = (int)BUFFER_SIZE / DataReceiver.BytesPerSector;
            ProgressStep = 100.0 / (double)PacksInSource;
            BytesPerSector = DataReceiver.BytesPerSector;
            NextPack();
            NextPack();
            Wait();
        }

        public void NextPack()
        {
            Wait();
            var beg = SectorBegin + PacksRead * SectorsInBuffer;
            var end = beg + SectorsInBuffer;

            IsFirstActive = !IsFirstActive;
            PacksRead++;
            TotalProgress += ProgressStep;
            Progress = (int)TotalProgress;

            if (EndIsNear) EndOfSource = true;
            if (end > DataReceiver.TotalSectors || end > SectorEnd)
            {
                end = DataReceiver.TotalSectors;
                EndIsNear = true;
            }
            if(beg > DataReceiver.TotalSectors || beg > SectorEnd || EndOfSource)
            {
                EndOfSource = true;
                return;
            }

            TaskDataReceiver = Task.Run(() =>
            {
                try
                {
                    if (IsFirstActive)
                    {
                        Array.Clear(BufferSecond, 0, BufferSecond.Length);
                        DataReceiver.DumpBuffer(beg, end, ref BufferSecond);
                        //Array.Copy(BufferFirst, BUFFER_LESS, BufferSecond, 0, 512);
                        if(EndIsNear)
                        {
                            int ts = BUFFER_SIZE - (int)((end - beg) * BytesPerSector);
                            int pos = BUFFER_SIZE - ts;
                            byte[] temp = new byte[ts];
                            Array.Copy(temp, 0, BufferSecond, pos, ts);
                        }
                    }
                    else
                    {
                        Array.Clear(BufferFirst, 0, BufferFirst.Length);
                        DataReceiver.DumpBuffer(beg, end, ref BufferFirst);
                        //Array.Copy(BufferSecond, BUFFER_LESS, BufferFirst, 0, 512);
                        if (EndIsNear)
                        {
                            int ts = BUFFER_SIZE - (int)((end - beg) * BytesPerSector);
                            int pos = BUFFER_SIZE - ts;
                            byte[] temp = new byte[ts];
                            Array.Copy(temp, 0, BufferFirst, pos, ts);
                        }
                    }
                }
                catch(Exception ex)
                {
                    Debug.WriteLine(ex.Message);
                }
            });
        }

        public byte[] GetBuffer()
        {
            return IsFirstActive ? BufferFirst : BufferSecond;
        }

        public byte[] GetBufferSector()
        {
            return BufferSector;
        }

        public void ReadSector(long sector)
        {
            Wait();
            DataReceiver.DumpBuffer(sector, sector+1, ref BufferSector);
            Wait();
        }

        private byte GetValue(int index)
        {
            if (index >= BUFFER_SIZE)
                throw new Exception("Out of range exception. DataProvader.GetValue(int index)");
            return IsFirstActive ? BufferFirst[index] : BufferSecond[index];
        }

        public void Close()
        {
            if (IsOpen) DataReceiver.Close();
            else throw new Exception("Data receiver is already closed");
            IsOpen = false;
        }

        private void Wait()
        {
            while (!TaskDataReceiver.IsCompleted) { }
        }
    }
}
