using System;
using System.Collections.Generic;
using System.IO;

namespace Lab_07
{
    static class Renamer
    {
        /// <summary>
        /// Renames only short name of file without parent directory and extention
        /// </summary>
        /// <param name="fullPath">File path</param>
        /// <param name="newName">New file name</param>
        /// <returns>New full path of the file</returns>
        public static string RenameOnlyName(string fullPath, string newName)
        {
            var fileInfo = new FileInfo(fullPath);
            var directoryPath = fileInfo.DirectoryName;
            var justName = Path.GetFileNameWithoutExtension(fullPath);
            var extention = fileInfo.Extension;

            var newFullPath = string.Format(@"{0}\{1}.{2}", directoryPath, newName, extention);

            newFullPath = newFullPath.Replace("..", ".");
            if (newFullPath[newFullPath.Length - 1] == '.')
                newFullPath = newFullPath.Remove(newFullPath.Length - 1, 1);

            File.Move(fullPath, newFullPath);
            return newFullPath;
        }

        /// <summary>
        /// Changes only extentio of file
        /// </summary>
        /// <param name="fullPath">Full file path</param>
        /// <param name="newExtention">New file extention</param>
        /// <returns>New file full path</returns>
        public static string ChangeExtention(string fullPath, string newExtention)
        {
            if (!File.Exists(fullPath))
                throw new Exception("FileNameWorker, Change Extention: File doesn't exists");

            var fileInfo = new FileInfo(fullPath);
            var directoryPath = fileInfo.DirectoryName;
            var justName = Path.GetFileNameWithoutExtension(fullPath);

            var newFullPath = string.Format(@"{0}\{1}.{2}", directoryPath, justName, newExtention);

            newFullPath = newFullPath.Replace("..", ".");
            if (newFullPath[newFullPath.Length - 1] == '.')
                newFullPath = newFullPath.Remove(newFullPath.Length - 1, 1);

            File.Move(fullPath, newFullPath);
            return newFullPath;
        }

        /// <summary>
        /// Adds zeros to beginning of file "15" -> "0015", "100" -> "0100"
        /// </summary>
        /// <param name="number">Number</param>
        /// <param name="digits">Length of result number</param>
        /// <returns>Zeros number</returns>
        public static string ConvertNumberToName(int number, int digits)
        {
            if (digits > 19) digits = 19;

            string result = "";

            for (long i = 10; i < Math.Pow(10, digits); i *= 10)
                if (number < i) result += "0";

            result += number.ToString();
            return result;
        }

        /// <summary>
        /// Checks if file exists and if so adds (N) to the end of file name
        /// </summary>
        /// <param name="desiredName">Desired name</param>
        /// <returns>Correct name</returns>
        public static string AvoidDuplicates(string desiredName)
        {
            FileInfo fileInfo = new FileInfo(desiredName);
            string nameNoExtension = Path.GetFileNameWithoutExtension(desiredName);
            string extension = fileInfo.Extension;
            string dir = fileInfo.DirectoryName;
            if (File.Exists(desiredName))
            {
                int copies = 2;
                while (File.Exists(string.Format(@"{0}\{1}({2}){3}", dir, nameNoExtension, copies, extension)))
                {
                    copies++;
                }
                return string.Format(@"{0}\{1}({2}){3}", dir, nameNoExtension, copies, extension);
            }
            else
            {
                return desiredName;
            }
        }

        public static string AvoidDuplicates(string desiredName, List<string> list)
        {
            FileInfo fileInfo = new FileInfo(desiredName);
            string nameNoExtension = Path.GetFileNameWithoutExtension(desiredName);
            string extension = Path.GetExtension(desiredName);
            string dir = Path.GetDirectoryName(desiredName);
            if (list.Contains(desiredName))
            {
                int copies = 2;
                while (list.Contains(string.Format(@"{0}\{1}({2}){3}", dir, nameNoExtension, copies, extension)))
                {
                    copies++;
                }
                return string.Format(@"{0}\{1}({2}){3}", dir, nameNoExtension, copies, extension);
            }
            else
            {
                return desiredName;
            }
        }

        public static void DeleteEmptySubdirectories(string path)
        {
            foreach (var directory in Directory.GetDirectories(path))
            {
                DeleteEmptySubdirectories(directory);
                if (Directory.GetFiles(directory).Length == 0 &&
                    Directory.GetDirectories(directory).Length == 0)
                {
                    Directory.Delete(directory, false);
                }
            }
        }
    }
}
