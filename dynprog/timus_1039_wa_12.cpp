// Draft solution for http://acm.timus.ru/problem.aspx?space=1&num=1018
// Wrong answer #12

#include <algorithm>
#include <cassert>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;

class solver
{
    vector<int> _ratings;
    vector<int> _parents;
    vector<vector<int>> _children;
    int _root;

    vector<pair<int,int>> _cache; // First element of the pair is the max cumulative rating of the subtree if its root is included
                                  // Second element is the max cumulative rating of the subtree if its root is not included

public:
    solver(const vector<int>& ratings, const vector<int>& parents) :
        _ratings(ratings),
        _parents(parents),
        _children(ratings.size()),
        _root(-1),
        _cache(ratings.size(), {-1, -1})
    {
        // Build the _children collection and
        // detect the root

        for (int i = 0; i < parents.size(); ++i)
        {
            if (parents[i] == -1)
            {
                assert(_root == -1);
                _root = i;
                continue;
            }

            _children[parents[i]].push_back(i);
        }

        assert(_root != -1);
    }

    int get_result()
    {
        pair<int, int> result = solve(_root);
        return max(result.first, result.second);
    }

    pair<int, int> solve(int sroot)
    {
        auto result = _cache[sroot];
        if (result != make_pair(-1, -1)) return result;

        result = make_pair(max(_ratings[sroot], 0), 0);

        for (int i : _children[sroot])
            result = make_pair(result.first + solve(i).second, result.second + solve(i).first);

        return _cache[sroot] = result;
    }
};

int main()
{
    int n;

    cin >> n;

    assert(n >= 1);
    assert(n <= 6000);

    vector<int> rating(n);

    for (int i = 0; i < n; ++i)
    {
        cin >> rating[i];
        assert(rating[i] >= -128);
        assert(rating[i] <= 127);
    }

    vector<int> parents(n, -1);

    for ( ; ; )
    {
        int child, parent;

        cin >> child >> parent;
        --child;
        --parent;

        if (child == -1 && parent == -1) break;

        assert(child >= 0);
        assert(child < n);
        assert(parent >= 0);
        assert(parent < n);
        assert(parents[child] == -1);

        parents[child] = parent;
    }

    cout << solver(rating, parents).get_result();
}
