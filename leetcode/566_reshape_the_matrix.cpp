// https://leetcode.com/problems/reshape-the-matrix

class Solution {
public:
    vector<vector<int>> matrixReshape(vector<vector<int>>& nums, int r, int c) {
        int orig_r = nums.size();
        int orig_c = nums[0].size();
        
        if (orig_r * orig_c != r * c) return nums;
        
        vector<vector<int>> result(1);
        
        for (auto&& v : nums)
            for (auto e : v)
            {
                if (result.back().size() == c)
                    result.resize(result.size() + 1);
                
                result.back().push_back(e);
            }
            
        return result;
    }
};
