public class Solution {
    public int[] TwoSum(int[] nums, int target) {
        var lookup = new Dictionary<int, int>();
        
        for (int i = 0; i < nums.Length; ++i)
        {
            if (lookup.TryGetValue(target - nums[i], out int index))
                return new[]{ index, i };
            lookup[nums[i]] = i;
        }
        
        return new int[]{};
    }
}
