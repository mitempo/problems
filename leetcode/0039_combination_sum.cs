// https://leetcode.com/problems/combination-sum/description/

public class Solution {
    IDictionary<int, IList<IList<int>>> d = new Dictionary<int, IList<IList<int>>>();
    
    public IList<IList<int>> CombinationSum(int[] candidates, int target, int minSoFar = int.MaxValue) {
        if (target < 0) return new List<IList<int>>();
        if (target == 0) return new List<IList<int>>{new List<int>()};
        
        List<IList<int>> r = new List<IList<int>>();

        foreach (int v in candidates.Where(e => e <= minSoFar).OrderByDescending(e => e))
            foreach (IList<int> l in CombinationSum(candidates, target - v, v))
                r.Add(l.Concat(new[]{v}).ToList());

        return r;
    }
}
