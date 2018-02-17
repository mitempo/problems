// https://leetcode.com/problems/regular-expression-matching/description/

class Solution {
public:
    bool isMatch(string s, string p) {
        return is_match(s.c_str(), p.c_str());
    }
    
    bool is_match(const char *s, const char *p)
    {
        if (*p == 0)
            return *s == 0;
        
        if (p[1] == '*')
        {
            return is_match(s, p + 2) ||
                   (*p == '.' && *s != 0 || *s == *p) && is_match(s + 1, p);
        }
        
        return (*s != 0 && *p == '.' || *s == *p) && is_match(s + 1, p + 1);
    }
};
