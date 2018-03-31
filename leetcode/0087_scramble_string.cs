// https://leetcode.com/problems/scramble-string/description/

public class Solution {
    public Dictionary<(string, string), bool> d = new Dictionary<(string, string), bool>();

    public bool IsScramble(string s1, string s2) {
        if (s1.Length != s2.Length) return false;

        int len = s1.Length;
        if (len == 1) return s1[0] == s2[0];
        if (len == 2) return s1[0] == s2[0] && s1[1] == s2[1] || s1[0] == s2[1] && s1[1] == s2[0];
        
        if (d.TryGetValue((s1, s2), out bool result)) return result;

        for (int i = 1; i < len; ++i)
            if (IsScramble(s1.Substring(0, i), s2.Substring(0, i)) && IsScramble(s1.Substring(i), s2.Substring(i)) ||
                IsScramble(s1.Substring(0, i), s2.Substring(len - i)) && IsScramble(s1.Substring(i), s2.Substring(0, len - i)))
                return d[(s1,s2)] = true;
        
        return d[(s1, s2)] = false;
    }
}
