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

        #region Delegates
        public delegate void DumpBufferDelegate(long sectorBegin, long sectorEnd, ref byte[] buffer);
        public delegate void OpenDelegate();
        public delegate void CloseDelegate();

        public readonly DumpBufferDelegate DumpBuffer;
        public readonly OpenDelegate Open;
        public readonly CloseDelegate Close;
        #endregion

        #region PUBLIC
        public int BytesPerSector { get; private set; }
        public long SourceLength { get; private set; }
        public long TotalSectors { get; private set; }
        #endregion

        #region PRIVATE
        private BinaryReader BinaryReader;
        private SafeFileHandle Handle;
        private int DiskId;
        private string ImagePath;
        private byte[] KOSTIL = new byte[BUFFER_SIZE];
        #endregion

        public DataReceiver(int diskId)
        {
            Open = Open_PhysicalDrive;
            Close = Close_PhysicalDrive;
            DumpBuffer = DumpBuffer_PhysicalDrive;

            DiskId = diskId;
            var diskGeometry = DiskGeometry.FromDevice(@"\\.\PHYSICALDRIVE" + DiskId.ToString());
            BytesPerSector = (int)diskGeometry.BytesPerSector;
            SourceLength = diskGeometry.DiskSize;
            TotalSectors = SourceLength / BytesPerSector;

            Open();
        }

        public DataReceiver(string imagePath)
        {
            Open = Open_Image;
            Close = Close_Image;
            DumpBuffer = DumpBuffer_Image;

            ImagePath = imagePath;
            BytesPerSector = 512;
            SourceLength = new FileInfo(ImagePath).Length;
            TotalSectors = SourceLength / BytesPerSector;

            Open();
        }

        #region Image
        private void Open_Image()
        {
            try
            {
                BinaryReader = new BinaryReader(File.Open(ImagePath, FileMode.Open));
            }
            catch (Exception ex)
            {
                throw ex;
            }
        }

        private void DumpBuffer_Image(long sectorBegin, long sectorEnd, ref byte[] buffer)
        {
            long distanceToMove = sectorBegin * BytesPerSector;
            if (sectorEnd > TotalSectors)
                throw new Exception("DataReceiver.DumpBuffer_Image: Last sector is bigger than file size");
            uint numBytesToRead = (uint)((sectorEnd - sectorBegin) * BytesPerSector);

            BinaryReader.BaseStream.Seek(distanceToMove, SeekOrigin.Begin);
            BinaryReader.Read(buffer, 0, (int)numBytesToRead);
        }

        public void Close_Image()
        {
            BinaryReader.Dispose();
        }
        #endregion

        #region Disk
        private void Open_PhysicalDrive()
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

        private void DumpBuffer_PhysicalDrive(long sectorBegin, long sectorEnd, ref byte[] buffer)
        {
            long distanceToMove = sectorBegin * BytesPerSector;
            if (sectorEnd > TotalSectors)
                throw new Exception("DataReceiver.DumpBuffer_PhysicalDrive: Last sector is bigger than disk size");
            uint numBytesToRead = (uint)((sectorEnd - sectorBegin) * BytesPerSector);

            IoCtl.SetFilePointerEx(Handle, distanceToMove, out long moveToHigh, 0);
            IoCtl.ReadFile(Handle, buffer, numBytesToRead, out uint numBytesRead, IntPtr.Zero);
            //Array.Copy(KOSTIL, 0, buffer, 512, numBytesToRead);
        }

        public void Close_PhysicalDrive()
        {
            Handle.Close();
        }
        #endregion
    }
}
