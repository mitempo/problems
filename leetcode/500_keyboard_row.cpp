// https://leetcode.com/problems/keyboard-row

class Solution {
public:
    uint32_t word_to_mask(const string& w)
    {
        uint32_t wmask = 0;
        for(char c : w)
            wmask |= 1 << tolower(c) - 'a';
        return wmask;
    }

    vector<string> findWords(vector<string>& words) {
        uint32_t row_nmasks[] =
        {
            ~word_to_mask("qwertyuiop"),
            ~word_to_mask("asdfghjkl"),
            ~word_to_mask("zxcvbnm")
        };
        
        vector<string> r;
        
        for (const auto& w : words)
        {
            uint32_t wmask = word_to_mask(w);
            
            if (find_if(begin(row_nmasks), end(row_nmasks), [wmask](uint32_t rownmask){ return (rownmask & wmask) == 0; }) != end(row_nmasks))
                r.push_back(w);
        }
        
        return r;
    }
};
