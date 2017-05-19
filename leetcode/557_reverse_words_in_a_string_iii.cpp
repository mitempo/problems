// https://leetcode.com/problems/reverse-words-in-a-string-iii

class Solution {
public:
    string reverseWords(string s) {
        for (auto p = s.begin(); ;)
        {
            while (p != s.end() && isspace(*p))
               ++p;

            if (p == s.end()) break;
            
            auto pwend = p + 1;
            while (pwend != s.end() && !isspace(*pwend))
               ++pwend;
               
            reverse(reverse_iterator<decltype(pwend)>(pwend), reverse_iterator<decltype(p)>(p));
            
            p = pwend;
        }

        return s;
    }
};
