// https://leetcode.com/problems/jump-game

class Solution {
public:
    bool canJump(vector<int>& nums) {
        if (nums.size() < 2) return true;

        for (int i = nums.size() - 1; i >= 0;)
        {
            if (nums[i] != 0)
            {
                --i;
                continue;
            }

            int j = i - 1;
            for (; j >= 0; --j)
                if (nums[j] > i - j - (i == nums.size() - 1))
                    break;
                
            if (j < 0) return false;
                
            i = j;
        }
        
        return true;
    }
};
