// https://leetcode.com/problems/subsets/description/

class Solution {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        return subsets(nums, 0);
    }
    
    vector<vector<int>> subsets(vector<int>& nums, int iStart) {
        vector<vector<int>> r;

        if (iStart >= nums.size())
        {
            r.push_back(vector<int>());
            return r;
        }
        
        for (auto&& ss : subsets(nums, iStart + 1))
        {
            r.push_back(ss);
            auto copy = ss;
            copy.push_back(nums[iStart]);
            r.push_back(copy);
        }
        
        return r;
    }
};