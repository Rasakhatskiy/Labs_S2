using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;

namespace Lab_07
{
    class Extractor
    {
        public int BytesPerSector { get; private set; }

        public int Progress { get; private set; }

        public bool IsCompleted { get; private set; }

        public bool IsFailed { get; private set; }

        public string ErrorMessage { get; private set; }

        public static string ResultFolder { get; private set; }





        const int SIZE_64_MB = 64 * 1024 * 1024;
        const int SIZE_08_MB = 8 * 1024 * 1024;
        const int SIZE_01_GB = 1024 * 1024 * 1024;


        private const int V = 32;

        public static byte[] Sign_32_FF = {
            0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
            0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
            0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
            0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, };





        DataWork.DataProvider DataProvider;
        StreamWriter StreamWriter;

        string TempName;
        string LogName;

        private long SectorBeg;
        private long SectorEnd;

        List<Parameter> Writers = new List<Parameter>();
        List<string> Names = new List<string>();

        bool STOP = false;

        double ProgresStep;
        double ProgressD = 0;





        public Extractor(int diskID, string resultPath, long firstSector, long lastSector)
        {
            IsFailed = false;
            Open(diskID);
            if (IsFailed) return;

            ResultFolder = resultPath;

            SectorBeg = firstSector;
            SectorEnd = lastSector;

            DataProvider.Launch(firstSector, lastSector);
            BytesPerSector = DataProvider.BytesPerSector;
        }


        private bool Open(int diskId)
        {
            try
            {
                DataProvider = new DataWork.DataProvider(diskId);
            }
            catch (Exception ex)
            {
                string busyText = "The process cannot access the file";
                if (ex.Message.Substring(0, busyText.Length) == busyText)
                    ErrorMessage = "Drive is being used by another process. Please close all applications that can use it and try again.";
                else
                    ErrorMessage = ex.Message + ex.StackTrace;
                IsFailed = true;
                return false;
            }
            return true;
        }

        public void Start()
        {
            if (IsFailed) return;
            IsCompleted = false;
            ErrorMessage = "No error message given";
            TempName = ResultFolder + "\\temp";
            LogName = ResultFolder + "\\Log.txt";
            Logger.SetPath(LogName);

            {
                var sectorsToRead = SectorEnd - SectorBeg;
                var sectorsPerPack = SIZE_64_MB / 512 - 1;
                var packsToRead = sectorsToRead / sectorsPerPack;
                ProgresStep = 100.0 / packsToRead;
            }

            if (File.Exists(LogName)) File.Delete(LogName);

            try
            {
                StreamWriter = new StreamWriter(File.Open(LogName, FileMode.OpenOrCreate));
                StreamWriter.Dispose();
                CutMain();
                Renamer.DeleteEmptySubdirectories(ResultFolder);
            }
            catch (Exception ex)
            {
                IsFailed = true;
                ErrorMessage = ex.Message + " " + ex.StackTrace;
            }
            finally
            {
                IsCompleted = true;
                Close();
            }
        }

        public void Stop()
        {
            STOP = true;
        }

        public void Close()
        {
            try { DataProvider.Close(); } catch (Exception) { }
            try { StreamWriter.Dispose(); } catch (Exception) { }
        }


        //Many small files, no FF block, No last block
        private void CutMain()
        {
            #region Var
            const int cameraOffset = 0x06;
            const int sizeOffset = 0x0C;
            const int dateTimeOffset = 0x10;
            const int spare = 0x200;
            byte[] signatureVideo = new byte[4] { 0x50, 0x55, 0x50, 0x41 };

            var position = spare;

            var lastPos = -1;
            var lastCam = -1;

            var cameraNumber = 0;
            var dateTimeInt = 0;
            var size = 0;

            var warning = false;
            var found_FF = false;
        #endregion

        #region Search
        HereWeGoAgain:
            while (position < SIZE_64_MB - spare && !STOP)
            {
                //if we didn't reach HYAV by offset of Size
                if (warning)
                {
                    //if we find FF block - everything is OK
                    if (SignatureFound(Sign_32_FF, position, DataProvider.GetBuffer()))
                    {
                        found_FF = true;
                        FillFile(lastCam, lastPos, position);
                        position += 0x200;
                        lastPos = position;
                        warning = false;
                    }
                }
                if (SignatureFound(signatureVideo, position, DataProvider.GetBuffer()))
                {
                    cameraNumber = DataProvider[position + cameraOffset];
                    size = Converter.ReadInt32(position + sizeOffset, DataProvider.GetBuffer());
                    dateTimeInt = Converter.ReadInt32(position + dateTimeOffset, DataProvider.GetBuffer());

                    //on/off last block
                    if (cameraNumber == lastCam)
                    {
                        //if we didn't reach HYAV by offset of Size AND didn't find FF block,
                        //don't write HYAV block
                        if (!(warning && !found_FF))
                        {
                            FillFile(lastCam, lastPos, position);
                        }
                    }

                    //create new parameter if doesn't exist
                    var parameter = FindCamera(Writers, cameraNumber);
                    if (parameter == null)
                    {
                        var valid =
                            ((cameraNumber == 2 || cameraNumber == 4 || cameraNumber == 5) && cameraNumber < 32) &&
                            (dateTimeInt > 0) &&
                            (size > 0);

                        if (valid)
                        {
                            parameter = new Parameter(TempName, cameraNumber, dateTimeInt);
                            Writers.Add(parameter);
                        }
                    }
                    else
                    {
                        //on/off FF
                        if (!((uint)dateTimeInt == 0xFFFFFFFF || (uint)size == 0xFFFFFFFF))
                        {
                            var d1 = parameter.LastDateTime;
                            var d2 = Converter.Convert_DHFS_ToDateTime(dateTimeInt);
                            var dif = (d2 - d1).TotalSeconds;

                            //check if you need small files 
                            var smallFiles = cameraNumber != lastCam;

                            //if we didn't reach HYAV by offset of Size AND didn't find FF block, new file begins
                            var wrongFF = warning && !found_FF;

                            if (dif < 0 || dif > 1 || smallFiles || wrongFF)
                            {
                                parameter.Close();
                                MoveFile(parameter.Path, parameter.CameraNumber + 1, parameter.FirstTimeInt, parameter.LastTimeInt);
                                parameter.Open(dateTimeInt);
                            }
                            parameter.LastTimeInt = dateTimeInt;
                            parameter.LastDateTime = d2;
                        }
                    }

                    lastCam = cameraNumber;
                    lastPos = position;
                    if (position + size < SIZE_64_MB - spare && size > 2)
                    {
                        if (SignatureFound(signatureVideo, position + size, DataProvider.GetBuffer()))
                        {
                            position += size - 2;
                        }
                        else warning = true;
                    }
                }
                position++;
            }
            #endregion

            #region Next buffer
            FillFile(lastCam, lastPos, position);
            if (!DataProvider.EndOfSource && !STOP)
            {
                position = spare;
                lastPos = spare;
                DataProvider.NextPack();

                ProgressD += ProgresStep;
                Progress = (int)ProgressD;
                goto HereWeGoAgain;
            }
            #endregion

            #region Close temp
            foreach (var item in Writers)
            {
                item.Close();
                //MoveFile(item.Path, item.CameraNumber + 1, item.FirstTimeInt, item.LastTimeInt);
                File.Delete(item.Path);
            }
            #endregion
        }

        private void FillFile(int lastCamera, int posBeg, int posEnd)
        {
            if (posBeg >= 0 && lastCamera >= 0)
            {
                var parameter = FindCamera(Writers, lastCamera);
                if (parameter != null)
                {
                    var toWrite = posEnd - posBeg;
                    if (toWrite > SIZE_08_MB - parameter.Position)
                    {
                        parameter.BinaryWriter.Write(parameter.Buffer, 0, parameter.Position);
                        parameter.BinaryWriter.Write(DataProvider.GetBuffer(), posBeg, toWrite);
                        parameter.Position = 0;
                    }
                    else
                    {
                        Array.Copy(DataProvider.GetBuffer(), posBeg, parameter.Buffer, parameter.Position, toWrite);
                        parameter.Position += toWrite;
                    }
                    parameter.Size += toWrite;
                    if (parameter.Size > SIZE_01_GB)
                    {
                        parameter.Close();
                        //MoveFile(parameter.Path, parameter.CameraNumber + 1, parameter.FirstTimeInt, parameter.LastTimeInt);
                        File.Delete(parameter.Path);
                        parameter.Open(parameter.LastTimeInt);
                    }
                }
            }
        }

        private bool SignatureFound(byte[] signature, int position, byte[] array)
        {
            try
            {
                for (int i = 0; i < signature.Length; i++)
                    if (array[position + i] != signature[i])
                        return false;

                return true;
            }
            catch (Exception ex)
            {
                var STOP = ex.Message;
            }
            return false;
        }

        private Parameter FindCamera(List<Parameter> list, int cameraNumber)
        {
            var matches = list.Where(p => p.CameraNumber == cameraNumber).ToList();
            if (matches.Count == 0) return null;
            else return matches[0];
        }

        private void MoveFile(string path, int camera, int dateTimeIntBeg, int dateTimeIntEnd)
        {
            var cameraName = camera < 10 ? "0" + camera.ToString() : camera.ToString();

            var timeBeg = Converter.Convert_DHFS_ToDateTime(dateTimeIntBeg);
            var timeEnd = Converter.Convert_DHFS_ToDateTime(dateTimeIntEnd);

            string name = $"{timeBeg:yyyy-MM-dd  HH-mm-ss}  --  {timeEnd:HH-mm-ss}";
            string folder = $@"{ResultFolder}\{cameraName}\{timeBeg:yyyy - MM - dd}\{timeBeg:HH}";
            name = $@"{folder}\{name}.h264";
            name = Renamer.AvoidDuplicates(name);

            var length = new FileInfo(path).Length;

            if (length < 0xFFFF)
            {
                File.Delete(path);
            }
            else
            {
                Directory.CreateDirectory(folder);
                Logger.Log(name);
                File.Move(path, name);
            }
        }
    }
}
