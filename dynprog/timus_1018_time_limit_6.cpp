#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <limits>
#include <algorithm>
#include <memory>
#include <tuple>
#include <map>
#include <set>
#include <queue>

using namespace std;

template <typename T> using v = vector<T>;
using uint = unsigned int;

int main()
{
    // Get the input data

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

    // Transform the tree to a more comfortable representation

    v<set<int>> children(n);
    v<uint> weights(n);

    queue<uint> node_queue;
    node_queue.push(0);

    while (!node_queue.empty())
    {
        uint node = node_queue.front();
        node_queue.pop();

        for (auto p = branches.begin(); p != branches.end();)
        {
            if (p->first.first != node && p->first.second != node)
            {
                ++p;
                continue;
            }

            uint child = p->first.first == node ? p->first.second : p->first.first;

            children[node].insert(child);
            weights[child] = p->second;
            node_queue.push(child);
            p = branches.erase(p);
        }
    }

    // Find the weights for all the root-based subtrees with number of branches up to q.

    using subtree = set<int>;                         // Subtree is represented as a subset of nodes from the full tree.
    using frontier = set<int>;                        // Frontier of a subtree: nodes that are not in the subtree, but their parents are.
    using frontier_and_weight = pair<frontier, uint>; // Frontier and weight of a subtree. Weight is the sub of weights of all branches.

    map<subtree, frontier_and_weight> subtrees;

    int root = 0;
    subtrees[{root}] = make_pair(children[root], weights[root]);

    for (uint i = 0; i < q; ++i)
    {
        for (const auto& p : subtrees)
        {
            const subtree& s = p.first;
            const frontier& f = p.second.first;
            uint weight = p.second.second;

            if (s.size() != i + 1) continue;

            for (auto c : f)
            {
                subtree deeper_subtree{ s };
                frontier deeper_frontier{ f };

                deeper_subtree.insert(c);
                deeper_frontier.erase(c);
                deeper_frontier.insert(children[c].cbegin(), children[c].cend());

                subtrees.insert(make_pair(move(deeper_subtree), make_pair(move(deeper_frontier), weight + weights[c])));
            }
        }
    }

    // Find the maximum-weight subtree with q branches.

    uint max_weight = numeric_limits<uint>::min();

    for (const auto& p : subtrees)
    {
        const subtree& s = p.first;
        uint weight = p.second.second;

        if (s.size() != q + 1) continue;
        if (weight > max_weight) max_weight = weight;
    }

    cout << max_weight;
}
