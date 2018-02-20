// https://leetcode.com/problems/combinations/description

public class Solution {
    public IList<IList<int>> Combine(int n, int k) {
        var r = new List<IList<int>>();
        Combine(n, k, 0, new List<int>(), r);
        return r;
    }

    public void Combine(int n, int k, int iStart, List<int> soFar, IList<IList<int>> r) {
        if (k > n - iStart) return;
        
        if (k <= 0)
        {
            r.Add(soFar);
            return;
        }
        
        for (int i = iStart; i < n; ++i)
            Combine(n, k - 1, i + 1, soFar.Concat(new[]{i + 1}).ToList(), r);
    }
}
