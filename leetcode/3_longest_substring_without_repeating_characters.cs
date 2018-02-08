// https://leetcode.com/problems/longest-substring-without-repeating-characters

public class Solution {
    public int LengthOfLongestSubstring(string s) {
        if (s.Length <= 1) return s.Length;

        var lastPos = new Dictionary<char, int>{{ s[0], 0 }};
        int curStart = 0;
        int maxSoFar = 1;

        for (int i = 1; i < s.Length; ++i)
        {
            if (lastPos.TryGetValue(s[i], out int lp) && lp >= curStart)
            {
                maxSoFar = Math.Max(maxSoFar, i - curStart);
                curStart = lp + 1;
            }

            lastPos[s[i]] = i;
        }

        return Math.Max(maxSoFar, s.Length - curStart);
    }
}
