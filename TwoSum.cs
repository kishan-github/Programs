/*****************************************************************************************************************
*
*  Find 2 indexs in an array whose sum is equal to target.
*
*
******************************************************************************************************************/

public class Solution {
    public int[] TwoSum(int[] nums, int target) {
        Dictionary<int, int> myDictionary = new Dictionary<int, int>();
        int[] result = new int[2];
        for (int i = 0; i < nums.Length; i++)
        {
            int numberToFindInDict = target - nums[i];
            if (myDictionary.TryGetValue(numberToFindInDict, out int value))
            {
                result[0] = i;
                result[1] = value;
                break;
            }
            else
            {
                myDictionary[nums[i]] = i;
            }
        }

        return result;
    }
}
