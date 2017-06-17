// https://leetcode.com/problems/longest-substring-without-repeating-characters

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        map<char, const char *> pos;
        int maxsofar = 0;
        
        const char *p = s.c_str(), *q = p;
        
        while (*q != 0)
        {
            auto palready = pos.find(*q);

            if (palready == pos.end())
            {
                pos[*q] = q;
                ++q;
                maxsofar = max(maxsofar, static_cast<int>(distance(p, q)));
                continue;
            }

            for (; p < palready->second + 1; ++p)
                pos.erase(*p);
        }
        
        return maxsofar;
    }
};

// Faster solution with vector for hash:

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        vector<const char *> pos(256);
        int maxsofar = 0;
        
        const char *p = s.c_str(), *q = p;
        
        while (*q != 0)
        {
            const char *palready = pos[*q];

            if (palready == nullptr)
            {
                pos[*q] = q;
                ++q;
                maxsofar = max(maxsofar, static_cast<int>(distance(p, q)));
                continue;
            }

            for (; p < palready + 1; ++p)
                pos[*p] = nullptr;
        }
        
        return maxsofar;
    }
};
