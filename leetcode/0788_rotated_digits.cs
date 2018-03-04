// https://leetcode.com/problems/rotated-digits/description/

public class Solution {
    public int RotatedDigits(int N) {
        int s = 0;
        for (int i = 1; i <= N; ++i)
            s += IsGood(i) ? 1 : 0;
        return s;
    }
    
    public bool IsGood(int n)
    {
        bool has2569 = false;
        for (; n > 0; n /= 10)
        {
            int d = n % 10;
            if (d == 3 || d == 4 || d == 7) return false;
            has2569 |= d == 2 || d == 5 || d == 6 || d == 9;
        }
        return has2569;
    }
}
