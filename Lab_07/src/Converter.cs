using System;
using System.Collections;
using System.Linq;

namespace Lab_07
{
    class Converter
    {
        public static DateTime Convert_DHFS_ToDateTime(int dateTimeArray)
        {
            //6 bits - x, x+2000 = year
            //4 bits - month
            //5 bits - day
            //5 bits - hours
            //6 bits - minutes
            //6 bits - seconds

            //If you want to get an array for the bits, you can use the BitArray.CopyTo method with a bool[] array.
            BitArray b = new BitArray(new int[] { dateTimeArray });
            int[] bits = b.Cast<bool>().Select(bit => bit ? 1 : 0).ToArray();

            Array.Reverse(bits);


            int years = 0 |
                (bits[0] << 5) |
                (bits[1] << 4) |
                (bits[2] << 3) |
                (bits[3] << 2) |
                (bits[4] << 1) |
                (bits[5] << 0);

            int months = 0 |
                (bits[6] << 3) |
                (bits[7] << 2) |
                (bits[8] << 1) |
                (bits[9] << 0);

            int days = 0 |
               (bits[10] << 4) |
               (bits[11] << 3) |
               (bits[12] << 2) |
               (bits[13] << 1) |
               (bits[14] << 0);

            int hours = 0 |
               (bits[15] << 4) |
               (bits[16] << 3) |
               (bits[17] << 2) |
               (bits[18] << 1) |
               (bits[19] << 0);

            int minutes = 0 |
               (bits[20] << 5) |
               (bits[21] << 4) |
               (bits[22] << 3) |
               (bits[23] << 2) |
               (bits[24] << 1) |
               (bits[25] << 0);

            int seconds = 0 |
               (bits[26] << 5) |
               (bits[27] << 4) |
               (bits[28] << 3) |
               (bits[29] << 2) |
               (bits[30] << 1) |
               (bits[31] << 0);

            DateTime result = new DateTime();
            result = result.AddYears(2000 + years - 1);
            result = result.AddMonths(months - 1);
            result = result.AddDays(days - 1);
            result = result.AddHours(hours);
            result = result.AddMinutes(minutes);
            result = result.AddSeconds(seconds);

            return result;
        }

        public static int ReadInt32(int position, byte[] buffer)
        {
            byte[] bytesArr = new byte[4];
            Array.Copy(buffer, position, bytesArr, 0, 4);
            return BitConverter.ToInt32(bytesArr, 0);
        }
    }
}
