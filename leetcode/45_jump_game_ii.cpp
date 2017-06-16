// https://leetcode.com/problems/jump-game-ii

class Solution {
public:
    int jump(vector<int>& nums) {
        int icur = 0;
        int steps = 0;
        int inext = -1;

        for (int i = 0; i < nums.size(); ++i)
        {
            if (i > icur)
            {
                icur = inext;
                ++steps;
            }
            
            inext = max(inext, i + nums[i]);
        }

        return steps;
    }
};
