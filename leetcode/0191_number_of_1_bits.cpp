// https://leetcode.com/problems/number-of-1-bits/description/

class Solution {
public:
    int hammingWeight(uint32_t n) {
        int s = 0;
        for (; n > 0; n >>= 1) s += n & 1;
        return s;
    }
};
