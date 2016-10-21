// https://leetcode.com/problems/trapping-rain-water

#include <vector>
#include <stack>

using namespace std;

struct elem
{
    int h;
    int w;
};

int trap(vector<int>& height)
{
    int acc = 0;
    int lefth = 0;

    stack<elem> stk;

    for (int i = 0; i < height.size(); ++i)
    {
        int w = 1;
        while (!stk.empty() && height[i] >= stk.top().h)
        {
            acc += (min(height[i], lefth) - stk.top().h) * stk.top().w;
            w += stk.top().w;
            stk.pop();
        }

        stk.push({height[i], w});

        if (stk.size() == 1) lefth = stk.top().h;
    }
    
    return acc;
}
