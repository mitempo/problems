// https://leetcode.com/problems/container-with-most-water

#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <limits>

using namespace std;

int maxArea(vector<int>& height)
{
    if (height.size() < 2) return 0;

    int result = numeric_limits<int>::min();

    auto pleft = height.cbegin();
    auto pright = prev(height.cend());

    for (int w = distance(pleft, pright); w > 0; --w)
    {
        result = max(result, min(*pleft, *pright) * w);
        if (*pleft < *pright)
            ++pleft;
        else
            --pright;
    }

    return result;
}

int main()
{
}
