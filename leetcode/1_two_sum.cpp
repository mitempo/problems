// https://leetcode.com/problems/two-sum

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        vector<int> result;
        
        if (nums.size() < 2) return result;

        vector<int> indices(nums.size());
        int iota = 0;
        for (auto& e : indices) e = iota++;

        sort(indices.begin(), indices.end(), [&nums](int i, int j){ return nums[i] < nums[j]; });
        
        int i = 0;
        int j = nums.size() - 1;

        for (int i = 0, j = nums.size() - 1; i < j; )
        {
            int candidate = nums[indices[i]] + nums[indices[j]];
            if (candidate == target) return {indices[i], indices[j]};
            if (candidate > target) --j; else ++i;
        }
    }
};
