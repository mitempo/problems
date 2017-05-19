// https://leetcode.com/problems/number-complement

class Solution {
public:
    int findComplement(int num) {
        int mask = 2;
        int temp = num;
        while (temp >>= 1)
            mask <<= 1;
        return num ^ (mask - 1);
    }
};
