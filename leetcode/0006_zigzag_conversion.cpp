// https://leetcode.com/problems/zigzag-conversion/description/

class Solution {
public:
    string convert(string s, int numRows) {
        if (numRows == 1) return s;
        
        int len = s.size();
        int step = numRows * 2 - 2;

        string r;
        r.reserve(s.size());

        for (int i = 0; i < numRows; ++i)
        {
            for (int j = 0; j < len; j += step)
            {
                if (j + i < len)
                    r += s[j + i];
                
                if (i > 0 && i < numRows - 1 && j + step - i < len)
                    r += s[j + step - i];
            }
        }

        return r;
    }
};
