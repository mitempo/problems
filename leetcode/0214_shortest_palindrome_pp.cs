// https://leetcode.com/problems/shortest-palindrome/description/

public class Solution {
    public string ShortestPalindrome(string s) {
        string rev = new string(s.Reverse().ToArray());

        for (int n = s.Length; n > 0; --n)
            if (isp(s, rev, n))
                return new string(s.Substring(n).Reverse().ToArray()) + s;
        
        return "";
    }
    
    public bool isp(string s, string rev, int n)
    {
        int off = s.Length - n;
        for (int i = 0; i < n; ++i)
            if (s[i] != rev[off + i])
                return false;
        return true;
    }
}
