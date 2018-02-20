// https://leetcode.com/problems/3sum/description/

public class Solution {
    public IList<IList<int>> ThreeSum(int[] nums) {
        Dictionary<int, int> cts = nums.GroupBy(k => k, (k, s) => (k, s.Count())).ToDictionary(pair => pair.Item1, pair => pair.Item2);

        return tsum(nums.OrderBy(e => e).ToArray(), cts).Select(e => new[] { e.Item1, e.Item2, - e.Item1 - e.Item2 }).ToArray();
    }

    public HashSet<(int, int)> tsum(int[] nums, Dictionary<int, int> cts) {
        HashSet<(int, int)> results = new HashSet<(int, int)>();

        for (int i = 0; i < nums.Length; ++i)
            for (int j = i + 1; j < nums.Length; ++j)
            {
                int v = - nums[i] - nums[j];

                if (v < nums[j]) continue;

                if (cts.TryGetValue(v, out int count) &&
                    (v == nums[i] && v == nums[j] ? count > 2 :
                     v == nums[i] || v == nums[j] ? count > 1 :
                                                    true))
                    results.Add((nums[i], nums[j]));
            }
        
        return results;
    }
}
