// https://leetcode.com/problems/generate-parentheses/description/

public class Solution {
    public IList<string> GenerateParenthesis(int n) {
        IList<string> result = new List<string>();
        GenerateParenthesis(n, 0, 0, "", result);
        return result;
    }

    public void GenerateParenthesis(int n, int o, int c, string soFar, IList<string> result) {
        if (c == n)
        {
            result.Add(soFar);
            return;
        }

        if (o < n) GenerateParenthesis(n, o + 1, c, soFar + "(", result);
        if (c < o) GenerateParenthesis(n, o, c + 1, soFar + ")", result);
    }
}
