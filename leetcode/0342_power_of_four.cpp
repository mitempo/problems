// https://leetcode.com/problems/power-of-four/description/

class Solution {
public:
    bool isPowerOfFour(int num) {
        return num > 0 && (num & 0x5555555555555555) && (num & (num - 1)) == 0;
    }
};
