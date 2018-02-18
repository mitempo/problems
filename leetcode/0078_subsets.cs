// https://leetcode.com/problems/subsets/description/

public class Solution {
    public IList<IList<int>> Subsets(int[] nums) {
        return Subsets(nums, 0).Select(e => e.ToArray()).ToArray();
    }

    public IEnumerable<IEnumerable<int>> Subsets(int[] nums, int iStart) {
        if (iStart > nums.Length - 1)
        {
            yield return Enumerable.Empty<int>();
            yield break;
        }
        
        foreach (IEnumerable<int> ss in Subsets(nums, iStart + 1))
        {
            yield return ss;
            yield return ss.Concat(new[]{nums[iStart]});
        }
    }
}
