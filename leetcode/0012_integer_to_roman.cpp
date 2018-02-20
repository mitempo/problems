// https://leetcode.com/problems/integer-to-roman/description/

class Solution {
public:
    map<int, const char*> m
    {
        {1000, "M"},
        {900, "CM"},
        {500, "D"},
        {400, "CD"},
        {100, "C"},
        {90, "XC"},
        {50, "L"},
        {40, "XL"},
        {10, "X"},
        {9, "IX"},
        {5, "V"},
        {4, "IV"},
        {1, "I"}
    };

    string intToRoman(int num) {
        string result;
        
        while (num > 0)
        {
            auto p = m.lower_bound(num);
            
            if (p == m.cend() || num < p->first) --p;

            result.append(p->second);
            num -= p->first;
        }
        
        return result;
    }
};
