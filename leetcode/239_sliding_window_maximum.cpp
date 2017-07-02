// https://leetcode.com/problems/sliding-window-maximum

class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        vector<int> r;
        
        if (nums.empty() || k <= 0) return r;
        
        deque<int> q;
        for (int i = 0; i < k; ++i)
        {
            while (!q.empty() && nums[q.back()] < nums[i])
                q.pop_back();
            q.push_back(i);
        }
        
        r.push_back(nums[q.front()]);

        for (int i = k; i < nums.size(); ++i)
        {
            if (q.front() <= i - k)
                q.pop_front();

            while (!q.empty() && nums[q.back()] < nums[i])
                q.pop_back();

            q.push_back(i);
            r.push_back(nums[q.front()]);
        }

        return r;
    }
};
