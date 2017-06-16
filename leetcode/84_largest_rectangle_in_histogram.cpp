// https://leetcode.com/problems/largest-rectangle-in-histogram

class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        heights.push_back(0);
        int maxsofar = 0;
        
        stack<pair<int, int>> s;
        
        for (int i = 0; i < heights.size(); ++i)
        {
            int istart = i;
            while (!s.empty() && s.top().second > heights[i])
            {
                istart = s.top().first;
                int candidate = (i - istart) * s.top().second;
                maxsofar = max(maxsofar, candidate);
                s.pop();
            }
            
            if (heights[i] > 0)
                s.push({istart, heights[i]});
        }
        
        return maxsofar;
    }
};
