using DiskManagement;
using Microsoft.Win32.SafeHandles;
using System;
using System.IO;
using System.Runtime.InteropServices;
using System.Threading;

namespace DataWork
{
    class DataReceiver
    {
        const int BUFFER_SIZE = 0x01008000 * 4;

        public int BytesPerSector { get; private set; }

        public long SourceLength { get; private set; }

        public long TotalSectors { get; private set; }

        private BinaryReader BinaryReader;
        private SafeFileHandle Handle;
        private int DiskId;
        private string ImagePath;
        private byte[] KOSTIL = new byte[BUFFER_SIZE];

        public DataReceiver(int diskId)
        {
            DiskId = diskId;
            var diskGeometry = DiskGeometry.FromDevice(@"\\.\PHYSICALDRIVE" + DiskId.ToString());
            BytesPerSector = (int)diskGeometry.BytesPerSector;
            SourceLength = diskGeometry.DiskSize;
            TotalSectors = SourceLength / BytesPerSector;

            Open();
        }

        private void Open()
        {
            try
            {
                Handle = IoCtl.CreateFile(
                    @"\\.\PHYSICALDRIVE" + DiskId.ToString(),
                    IoCtl.GENERIC_READ,
                    0,
                    IntPtr.Zero,
                    IoCtl.OPEN_EXISTING,
                    0,
                    IntPtr.Zero);

                if (Handle.IsInvalid)
                {
                    Marshal.ThrowExceptionForHR(Marshal.GetHRForLastWin32Error());
                }
            }
            catch (Exception ex)
            {
                throw ex;
            }
        }

        public void DumpBuffer(long sectorBegin, long sectorEnd, ref byte[] buffer)
        {
            long distanceToMove = sectorBegin * BytesPerSector;
            if (sectorEnd > TotalSectors)
                throw new Exception("DataReceiver.DumpBuffer_PhysicalDrive: Last sector is bigger than disk size");
            uint numBytesToRead = (uint)((sectorEnd - sectorBegin) * BytesPerSector);

            IoCtl.SetFilePointerEx(Handle, distanceToMove, out long moveToHigh, 0);
            IoCtl.ReadFile(Handle, buffer, numBytesToRead, out uint numBytesRead, IntPtr.Zero);
            //Array.Copy(KOSTIL, 0, buffer, 512, numBytesToRead);
        }

        public void Close()
        {
            Handle.Close();
        }
    }
}
