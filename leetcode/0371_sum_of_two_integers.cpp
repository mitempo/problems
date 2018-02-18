// https://leetcode.com/problems/sum-of-two-integers/submissions/1

class Solution {
public:
    int getSum(int a, int b) {
        int r = a ^ b;
        int c = a & b;
        
        while (c)
        {
            c <<= 1;
            int oldr = r;
            r ^= c;
            c &= oldr;
        }
        
        return r;
    }
};
