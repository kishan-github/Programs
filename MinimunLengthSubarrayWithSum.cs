/******************************************************************************

Find the minimum length of sub array which have sum greater than or equal to given number.

*******************************************************************************/
using System;
class HelloWorld {
  static void Main() {
    int[] arr = {2,3,1,2,4,3};
    int target = 7;
    Console.WriteLine("minimun number of values = " + GetMinNumberofValues(arr, target));
  }
  
  static int GetMinNumberofValues(int[] arr, int target) {
        if (arr == null || arr.Length == 0)
            return 0;

        int left = 0, right = 0, total = 0, count = int.MaxValue;

        while (right < arr.Length) {
            total += arr[right];

            while (total >= target) {
                count = Math.Min(count, right - left + 1);
                total -= arr[left];
                left++;
            }

            right++;
        }

        return count == int.MaxValue ? 0 : count;
    }
}
