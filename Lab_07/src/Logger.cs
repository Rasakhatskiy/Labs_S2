using System;
using System.IO;

namespace Lab_07
{
    static class Logger
    {
        public static string Path { get; private set; } = "Log.txt";

        public static void SetPath(string path)
        {
            Path = path;
        }

        public static void Log(string message, bool time = false)
        {
            if(File.Exists(Path))
            {
                using (var StreamWriter = new StreamWriter(Path, append: true))
                {
                    if (time)
                    {
                        message = DateTime.Now.ToString("[HH:mm:ss] : ") + message;
                    }
                    StreamWriter.WriteLine(message);
                }
            }
            else
            {
                using (var StreamWriter = new StreamWriter(File.Open(Path, FileMode.OpenOrCreate)))
                {
                    StreamWriter.WriteLine(DateTime.Now.ToString("[yyyy.MM.dd]"));
                    if(time)
                    {
                        message = DateTime.Now.ToString("[HH:mm:ss] : ") + message;
                    }
                    StreamWriter.WriteLine(message);
                }
            }
        }

    }
}
