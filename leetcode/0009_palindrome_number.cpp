// https://leetcode.com/problems/palindrome-number/description/

class Solution {
public:
    int reverse(int x)
    {
        int s = 0;
        while (x)
        {
            s = s * 10 + x % 10;
            x /= 10;
        }
        return s;
    }

    bool isPalindrome(int x) {
        return x >= 0 && reverse(x) == x;
    }
};
