// https://leetcode.com/problems/permutations-ii/description/

public class Solution {
    public IList<IList<int>> PermuteUnique(int[] nums) {
        Array.Sort(nums);
        List<IList<int>> r = new List<IList<int>>{nums.ToArray()};
        
        for ( ; ; )
        {
            int i = nums.Length - 2;
            while (i >= 0 && nums[i] >= nums[i+1]) --i;
            if (i < 0) break;
            
            int j = nums.Length - 1;
            while (nums[j] <= nums[i]) --j;
            
            int t = nums[i];
            nums[i] = nums[j];
            nums[j] = t;
            
            Array.Reverse(nums, i + 1, nums.Length - i - 1);
            r.Add(nums.ToArray());
        }
        
        return r;
    }
}
