// Solution for http://acm.timus.ru/problem.aspx?space=1&num=1018

#include <iostream>
#include <utility>
#include <vector>
#include <limits>
#include <algorithm>
#include <map>
#include <queue>
#include <cassert>

using namespace std;

template <typename T> using v = vector<T>;
using uint = unsigned int;

const uint NaN = numeric_limits<uint>::max();

// Addition with "NaN": "NaN" + number = "NaN"
uint add_with_nan(uint a, uint b)
{
    return a == NaN || b == NaN ? NaN : a + b;
}

class solver
{
    size_t _n; // Number of nodes
    v<v<int>> _children;
    v<int> _bweights;

    v<int> _sweights;                         // Memoized weights of subtrees with a given root
    v<int> _ssizes;                           // Memoized number of nodes in subtrees with a given root
    map<pair<int, uint>, int> _cut_sweights;  // Memoized weights of subtrees with a given root and a given number of branches cut

public:
    solver(map<pair<int, int>, uint>& branches) :
        _n(branches.size() + 1),
        _children(_n),
        _bweights(_n),
        _ssizes(_n, -1),
        _sweights(_n, -1)
    {
        // Transform the tree into a more comfortable representation

        queue<int> node_queue;
        node_queue.push(0);

        while (!node_queue.empty())
        {
            int node = node_queue.front();
            node_queue.pop();

            for (auto p = branches.begin(); p != branches.end();)
            {
                if (p->first.first != node && p->first.second != node)
                {
                    ++p;
                    continue;
                }

                uint child = p->first.first == node ? p->first.second : p->first.first;

                _children[node].push_back(child);
                _bweights[child] = p->second;
                node_queue.push(child);
                p = branches.erase(p);
            }
        }

        // Check if the tree is a proper binary tree

        for (auto& e : _children) assert(e.empty() || e.size() == 2);
    }

    // Calculates weight of a subtree with a given root
    uint get_subtree_weight(int sroot)
    {
        return _sweights[sroot] != -1 ? _sweights[sroot] :
                                        (_sweights[sroot] = _bweights[sroot] +
                                                            (_children[sroot].empty() ? 0 : get_subtree_weight(_children[sroot][0]) +
                                                                                            get_subtree_weight(_children[sroot][1])));
    }

    // Calculates number of nodes in a subtree with a given root
    uint get_subtree_size(int sroot)
    {
        return _ssizes[sroot] != -1 ? _ssizes[sroot] :
                                      (_ssizes[sroot] = 1 +
                                                        (_children[sroot].empty() ? 0 : get_subtree_size(_children[sroot][0]) +
                                                                                        get_subtree_size(_children[sroot][1])));
    }

    uint max_cut_of_subtree(int sroot, uint n_to_cut)
    {
        auto key = make_pair(sroot, n_to_cut);
        auto p = _cut_sweights.lower_bound(key);
        if (p != _cut_sweights.end() && p->first == key) return p->second;

        if (n_to_cut == 0)
            return _cut_sweights.insert(p, make_pair(key, get_subtree_weight(sroot)))->second;

        if (get_subtree_size(sroot) < n_to_cut)
            return _cut_sweights.insert(p, make_pair(key, NaN))->second;

        if (get_subtree_size(sroot) == n_to_cut)
            return _cut_sweights.insert(p, make_pair(key, 0))->second;

        uint max_cut = numeric_limits<uint>::min();

        for (uint i = 0; i <= n_to_cut; ++i)
        {
            uint left  = max_cut_of_subtree(_children[sroot][0], i);
            uint right = max_cut_of_subtree(_children[sroot][1], n_to_cut-i);

            uint cut = add_with_nan(add_with_nan(left, right), _bweights[sroot]);
            if (cut != NaN && cut > max_cut) max_cut = cut;
        }

        return _cut_sweights.insert(p, make_pair(key, max_cut))->second;
    }
};

int main()
{
    uint n; // Number of nodes
    uint q; // Target number of branches

    cin >> n >> q;

    map<pair<int, int>, uint> branches;

    for (uint i = 0; i < n - 1; ++i)
    {
        int start, end;
        uint weight;

        cin >> start >> end >> weight;
        if (start > end) swap(start, end);
        branches[make_pair(start - 1, end - 1)] = weight;
    }

    cout << solver(branches).max_cut_of_subtree(0, n-1-q);
}
