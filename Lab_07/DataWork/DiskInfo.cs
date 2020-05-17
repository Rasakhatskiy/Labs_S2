using DiskManagement;
using System.Collections.Generic;
using System.IO;
using System.Management;

namespace DataWork
{
    internal class DiskInfo
    {
        public int id;
        public int bytesPerSector;
        public string model;
        public long numberOfSectors;
        public long size;
        public DiskInfo(int id, int bytesPerSector, string model, long numberOfSectors, long size)
        {
            this.id = id;
            this.model = model;
            this.numberOfSectors = numberOfSectors;
            this.size = size;
            this.bytesPerSector = bytesPerSector;
        }
        public static List<DiskInfo> GetDiskInfoList()
        {
            List<DiskInfo> diskInfoList = new List<DiskInfo>();

            try
            {
                ManagementObjectSearcher searcher =
                    new ManagementObjectSearcher("root\\CIMV2",
                    "SELECT * FROM Win32_DiskDrive");


                foreach (ManagementObject queryObj in searcher.Get())
                {
                    var id = queryObj["DeviceID"];
                    var diskGeometry = DiskGeometry.FromDevice(id.ToString());
                    var model = queryObj["Model"];
                    var sectors = diskGeometry.MaximumLinearAddress;
                    var size = queryObj["Size"];
                    var bytesPerS = queryObj["BytesPerSector"];
                    if (size == null || model == null || sectors == null || id == null || bytesPerS == null)
                        continue;
                    long sizeL = long.Parse(size.ToString()) / 1024 / 1024 / 1024 + 1;
                    char last = id.ToString()[id.ToString().Length - 1];
                    int diskNum = int.Parse(last.ToString());
                    DiskInfo diskInfo = new DiskInfo(diskNum, int.Parse(bytesPerS.ToString()), model.ToString(), long.Parse(sectors.ToString()), sizeL);
                    diskInfoList.Add(diskInfo);
                }

                diskInfoList.Sort((s1, s2) => s1.id.CompareTo(s2.id));
            }
            catch (ManagementException)
            {
                return diskInfoList;
            }
            return diskInfoList;
        }

        public static long GetTotalFreeSpace(string driveName)
        {
            foreach (DriveInfo drive in DriveInfo.GetDrives())
            {
                if (drive.IsReady && drive.Name == driveName)
                {
                    return drive.TotalFreeSpace;
                }
            }
            return -1;
        }
    }
}