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
        int *pi;
        int min;
        int step;

        if (lefth <= righth)
        {
            pi = &ileft;
            min = lefth;
            step = 1;
        }
        else
        {
            pi = &iright;
            min = righth;
            step = -1;
        }
        
        if (height[*pi] <= min)
        {
            acc += min - height[*pi];
            *pi += step;
        }
        else
            (pi == &ileft ? lefth : righth) = height[*pi];
                
    }

    return acc;
}
