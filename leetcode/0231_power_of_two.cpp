// https://leetcode.com/problems/power-of-two/description/

class Solution {
public:
    bool isPowerOfTwo(int n) {
        return n > 0 && (n - 1 & n) == 0;
    }
};
