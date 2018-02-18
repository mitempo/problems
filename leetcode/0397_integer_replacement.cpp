// https://leetcode.com/problems/integer-replacement/description/

class Solution {
public:
    int integerReplacement(long n, int d = 0) {
        return n == 1
            ? d
            : n % 2 == 0
                ? integerReplacement(n / 2, d + 1)
                : min(integerReplacement(n + 1, d + 1), integerReplacement(n - 1, d + 1));
    }
};
