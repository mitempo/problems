// https://leetcode.com/problems/shortest-palindrome/description/

public class Solution {
    public string ShortestPalindrome(string s) {
        if (s.Length < 2) return s;
        
        string st = intersperse(s);
        int i = st.Length / 2;

        for (; i >= 0; --i)
            if (IsCandidate(st, i))
                break;

        return revert(new string(st.Substring(i * 2 + 1).Reverse().ToArray()) + st);
    }

    private string intersperse(string s)
    {
        if (s.Length < 2) return s;

        var sb = new StringBuilder();
        sb.Append(s[0]);

        for (int i = 1; i < s.Length; ++i)
        {
            sb.Append('#');
            sb.Append(s[i]);
        }
        
        return sb.ToString();
    }

    private string revert(string s)
    {
        if (s.Length < 2) return s;

        var sb = new StringBuilder();

        for (int i = 0; i < s.Length; i += 2)
            sb.Append(s[i]);
        
        return sb.ToString();
    }

    private bool IsCandidate(string s, int i)
    {
        if (i > s.Length / 2) return false;

        for (int j = i-- + 1; i >= 0;)
            if (s[i--] != s[j++])
                return false;
        
        return true;
    }
}
