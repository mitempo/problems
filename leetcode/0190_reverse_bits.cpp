https://leetcode.com/problems/reverse-bits/description/

class Solution {
public:
    uint32_t reverseBits(uint32_t n) {
        uint32_t r = 0;
        
        for (int i = 0; i < 32; ++i, n >>= 1)
            r = (r << 1) | (n & 1);
        
        return r;        
    }
};
