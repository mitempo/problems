// https://leetcode.com/problems/reverse-integer/description/

public class Solution {
    public int Reverse(int x) {
        return x == 0 ? 0 : int.TryParse((x < 0 ? "-" : "") + new string((x < 0 ? -x : x).ToString().Reverse().ToArray()).TrimStart('0'), out int result) ? result : 0;
    }
}
