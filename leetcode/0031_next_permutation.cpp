// https://leetcode.com/problems/permutations

class Solution {
public:
    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int>> r;
        permute(nums, 0, r);
        return r;
    }
    
    void permute(vector<int>& nums, int iStart, vector<vector<int>>& r)
    {
        if (iStart >= nums.size())
        {
            r.push_back(nums);
            return;
        }
        
        for (int i = iStart; i < nums.size(); ++i)
        {
            swap(nums[iStart], nums[i]);
            permute(nums, iStart + 1, r);
            if (i < nums.size() - 1)
                reverse(nums.begin() + iStart + 1, nums.end());
        }
    }
};
