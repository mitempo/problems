// https://leetcode.com/problems/array-partition-i

class Solution {
public:
    int arrayPairSum(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        
        int s = 0;
        for (auto p = nums.cbegin(); p != nums.cend(); p += 2)
            s += *p;
            
        return s;
    }
};
