// http://leetcode.com/problems/maximal-rectangle/

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

class Solution
{
public:
    int maximalRectangle(vector<vector<char>>& matrix)
    {
        if (matrix.empty() || matrix[0].empty()) return 0;
        
        vector<vector<int>> d(matrix[0].size(), vector<int>(matrix[0].size(), 0));

        int maxsq = 0;
        
        for (int i = 0; i < matrix.size(); ++i)
        {
            for (int j = 0; j < matrix[i].size(); ++j)
            {
                bool f = true;
                for (int k = j; k >= 0; --k)
                {
                    if (f &= matrix[i][k] == '1')
                        maxsq = max(maxsq, ++d[j][k] * (j-k+1));
                    else
                        d[j][k] = 0;
                }
            }
        }

        return maxsq;
    }
};
