// https://leetcode.com/problems/longest-common-prefix/description/

public class Solution {
    public string LongestCommonPrefix(string[] strs) {
        if (strs.Length == 0) return "";
        return strs.Skip(1).Aggregate(strs.First(), (s, acc) => new string(s.Zip(acc, (a, b) => (a, b)).TakeWhile(pair => pair.Item1 == pair.Item2).Select(pair => pair.Item1).ToArray()));
    }
}
