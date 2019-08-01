// https://leetcode.com/problems/reverse-integer/description

class Solution {
public:
    int reverse(int x) {
        if (x == 0) return 0;
        bool isneg = x < 0;
        string s = to_string(x < 0 ? -x : x);
        std::reverse(begin(s), end(s));
        try
        {
            return stoi((x < 0 ? "-" : "") + s.substr(s.find_first_not_of('0')));
        }
        catch (...)
        {
            return 0;
        }
    }
};