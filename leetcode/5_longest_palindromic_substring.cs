// https://leetcode.com/problems/longest-palindromic-substring

public class Solution {
    public string LongestPalindrome(string s) {
        if (s.Length <= 1) return s;

        (int, int) bounds = (0, 0);
        int maxSoFar = 0;

        for (int i = 1; i < s.Length; ++i)
        {
            for (int o = 0; o <= i && i + o < s.Length && s[i - o] == s[i + o]; ++o)
            {
                if (o * 2 + 1 > maxSoFar)
                {
                    maxSoFar = o * 2 + 1;
                    bounds = (i - o, i + o);
                }
            }

            for (int o = 0; o <= i - 1 && i + o < s.Length && s[i - o - 1] == s[i + o]; ++o)
            {
                if (o * 2 + 2 > maxSoFar)
                {
                    maxSoFar = o * 2 + 2;
                    bounds = (i - o - 1, i + o);
                }
            }
        }
        
        return s.Substring(bounds.Item1, bounds.Item2 - bounds.Item1 + 1);
    }
}
