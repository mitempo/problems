// https://leetcode.com/problems/trapping-rain-water

#include <vector>

using namespace std;

int trap(vector<int>& height)
{
    if (height.size() < 3) return 0;
    
    int ileft = 0;
    int iright = height.size()-1;

    int lefth = height[ileft];
    int righth = height[iright];
    
    int acc = 0;
    
    while (ileft <= iright)
    {
        int minh = min(lefth, righth);
        int *pi = minh == lefth ? &ileft : &iright;

        if (height[*pi] <= minh)
        {
            acc += minh - height[*pi];
            *pi += pi == &ileft ? 1 : -1;
        }
        else
            (pi == &ileft ? lefth : righth) = height[*pi];
    }

    return acc;
}
