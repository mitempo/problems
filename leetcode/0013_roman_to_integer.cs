// https://leetcode.com/problems/roman-to-integer/description/

public class Solution {
    public (string, int)[] m = new (string, int)[]
    {
        ("M", 1000),
        ("CM", 900),
        ("D", 500),
        ("CD", 400),
        ("C", 100),
        ("XC", 90),
        ("L", 50),
        ("XL", 40),
        ("X", 10),
        ("IX", 9),
        ("V", 5),
        ("IV", 4),
        ("I", 1)
    };

    public int RomanToInt(string s) {
        int r = 0;
        
        while (s.Length > 0)
        {
            var item = m.First(e => s.StartsWith(e.Item1));
            r += item.Item2;
            s = s.Remove(0, item.Item1.Length);
        }

        return r;
    }
}
