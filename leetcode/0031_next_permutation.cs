// https://leetcode.com/problems/next-permutation/description/

public class Solution {
    public void NextPermutation(int[] nums) {
        if (nums.Length < 2) return;

        int i = nums.Length - 2;

        for (; i >= 0 && nums[i] >= nums[i+1]; --i)
            ;

        int j = i + 1;
        for (int k = nums.Length - 1; j < k; ++j, --k)
        {
            var e = nums[j];
            nums[j] = nums[k];
            nums[k] = e;
        }
        
        if (i < 0) return;

        j = i + 1;
        for (; j < nums.Length && nums[j] <= nums[i]; ++j)
            ;
        
        if (j >= nums.Length) return;
        
        var t = nums[i];
        nums[i] = nums[j];
        nums[j] = t;
    }
}
