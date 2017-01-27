// https://leetcode.com/problems/spiral-matrix/

#include <vector>
#include <iostream>
#include <utility>

using namespace std;

class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix)
    {
        vector<int> r;

        if (matrix.empty() || matrix[0].empty()) return r;
        
        auto at = [&](pair<int,int> ij) { return matrix[ij.first][ij.second]; };
        
        auto turn = [](pair<int, int> diff)
        {
            return diff == make_pair(0, 1) ? make_pair(1, 0) :
                   diff == make_pair(1, 0) ? make_pair(0, -1) :
                   diff == make_pair(0, -1) ? make_pair(-1, 0) :
                   diff == make_pair(-1, 0) ? make_pair(0, 1) : make_pair(0, 0);
        };
        
        auto less = [](pair<int,int> a, pair<int,int> b) { return a.first < b.first && a.second < b.second; };
        auto plus = [](pair<int,int> a, pair<int,int> b) { return make_pair(a.first + b.first, a.second + b.second); };
        auto minus = [](pair<int,int> a, pair<int,int> b) { return make_pair(a.first - b.first, a.second - b.second); };

        auto tl = make_pair(0, 0);
        auto br = make_pair(static_cast<int>(matrix.size()), static_cast<int>(matrix[0].size()));
        
        auto ij = make_pair(0, 0);
        auto diff = make_pair(0, 1);
        
        while (less({0, 0}, minus(br, tl)))
        {
            for ( ; ij.first >= tl.first && ij.first < br.first && ij.second >= tl.second && ij.second < br.second; ij = plus(ij,diff))
                r.push_back(at(ij));
            
            ij = minus(ij, diff);
            diff = turn(diff);
            if (diff.first + diff.second > 0) tl = plus(tl, diff); else br = plus(br, diff);
            ij = plus(ij, diff);
        }
        
        return r;
    }
};

int main()
{
    vector<vector<int>> v = { { 1, 2, 3}, {4, 5, 6}, {7, 8, 9}};

    for (auto&& a : Solution().spiralOrder(v)) cout << a << " ";
}
