// https://leetcode.com/problems/valid-parentheses/description/

public class Solution {
    public Dictionary<char, char> par = new Dictionary<char, char>
    {
        {'(', ')'},
        {'[', ']'},
        {'{', '}'},
    };

    public bool IsValid(string s) {
        Stack<char> st = new Stack<char>();
        foreach (char c in s)
        {
            if (par.TryGetValue(c, out char mirror))
                st.Push(mirror);
            else
            {
                if (st.Count == 0 || st.Peek() != c) return false;
                st.Pop();
            }
        }
        return st.Count == 0;
    }
}
