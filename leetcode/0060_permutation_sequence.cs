// https://leetcode.com/problems/permutation-sequence/description/

public class Solution {
    public int fact(int n)
    {
        return n <= 0 ? 1 : n * fact(n-1);
    }

    public string GetPermutation(int n, int k) {
        return GetPermutation(Enumerable.Range(0, n).Select(e => (char)('1' + e)).ToList(), k - 1);
    }

    public string GetPermutation(List<char> cs, int k) {
        if (cs.Count == 1) return new string(new[]{cs[0]});

        int step = fact(cs.Count - 1);
        int i = k / step;
        char lead = cs[i];
        cs.RemoveAt(i);
        return lead + GetPermutation(cs, k % step); 
    }
}
