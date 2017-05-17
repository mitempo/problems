// https://leetcode.com/problems/hamming-distance

class Solution {
public:
    int hammingDistance(int x, int y) {
        int d = 0;
        for (x ^= y; x; x &= x - 1)
            ++d;
        return d;
    }
};
