public class Solution {
    public int[] TwoSum(int[] nums, int target) {
        int[] indices = Enumerable.Range(0, nums.Length).OrderBy(e => nums[e]).ToArray();
        int i = 0, j = nums.Length - 1;
        while (j > i)
        {
            int sum = nums[indices[i]] + nums[indices[j]];
            if (sum > target) --j;
            else if (sum < target) ++i;
            else break;
        }
        return new[]{ indices[i], indices[j] };
    }
}
