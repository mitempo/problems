// https://leetcode.com/problems/palindrome-partitioning/description/

public class Solution {
    public IList<IList<string>> Partition(string s) {
        var r = new List<IList<string>>();
        part(s, new List<string>(), r);
        return r;
    }

    private void part(string s, IList<string> candidate, IList<IList<string>> r)
    {
        if (s == "")
        {
            r.Add(candidate);
            return;
        }

        for (int n = 1; n <= s.Length; ++n)
        {
            string head = s.Substring(0, n);
            if (!IsPalindrome(head)) continue;
            part(s.Substring(n), candidate.Concat(new[]{head}).ToList(), r);
        }
    }
    
    public bool IsPalindrome(string s)
    {
        for (int i = 0, j = s.Length - 1; i < j; ++i, --j)
            if (s[i] != s[j])
                return false;
        
        return true;
    }
}
