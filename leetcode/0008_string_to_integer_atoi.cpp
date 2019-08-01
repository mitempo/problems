// https://leetcode.com/problems/string-to-integer-atoi/description/

class Solution {
public:
    int myAtoi(string str) {
        const char *p = str.c_str();

        while (iswspace(*p)) ++p;
        int mult = *p == '+' ? (++p, 1) :
                   *p == '-' ? (++p, -1) :
                   1;

        int r = 0;
        for (; ; ++p)
        {
            char c = *p;
            if (c < '0' || c > '9') return r;
            long long new_r = (long long)r * 10 + (c - '0') * mult;
            if (new_r > INT_MAX) return INT_MAX;
            if (new_r < INT_MIN) return INT_MIN;
            r = (int)new_r;
        }
        
        return r;
    }
};