// Draft solution for http://acm.timus.ru/problem.aspx?space=1&num=1078 ("Segments")
// WA #2

#include <cassert>
#include <iostream>
#include <iterator>
#include <map>
#include <set>
#include <vector>
#include <utility>

using namespace std;

int main()
{
    int n;

    cin >> n;

    vector<pair<int, int>> segments;  // Starts and ends for all segments

    for (int i = 0; i < n; ++i)
    {
        int start;
        int end;

        cin >> start >> end;

        assert(start < end); // This is not explicitly stated in the problem, but let's try
        segments.push_back({ start, end });
    }

    map<pair<int, bool>, set<int>> index; // Maps a {coordinate, is_start} to numbers of all the segments
                                          // starting (if the flag is true) or ending (if the flag is false)
                                          // at that coordinate

    for (int i = 0; i < segments.size(); ++i)
    {
        index[{segments[i].first, true}].insert(i);
        index[{segments[i].second, false}].insert(i);
    }

    vector<unsigned> deepest_child_depth(n);
    vector<int> deepest_child(n, -1);
    vector<set<int>> candidates(n);

    for (auto p = next(begin(index)); p != end(index); ++p)
    {
        if (p->first.second)
        {
            for (auto q = p; q != begin(index); --q)
                if (prev(q)->first.second) // Only for the entries with starting points
                    for (int i : prev(q)->second)
                        candidates[i].insert(p->second.cbegin(), p->second.cend());
        }
        else
        {
            for (int i : p->second) // Elements ending here
            {
                unsigned this_depth = deepest_child_depth[i] + 1;

                for (int j = 0; j < n; ++j)  // Candidate parents
                {
                    if (candidates[j].find(i) == candidates[j].end()) continue;

                    if (deepest_child_depth[j] < this_depth)
                    {
                        deepest_child_depth[j] = this_depth;
                        deepest_child[j] = i;
                    }
                }

                for (auto q = p; q != begin(index); --q)
                    prev(q)->second.erase(i);
            }
        }
    }

    // Verify that all the starts ended
    for (auto e : index) if (e.first.second) assert(e.second.empty());

    unsigned max_child_depth = 0;
    int iDeepest = 0;

    for (int i = 0; i < n; ++i)
    {
        if (deepest_child_depth[i] > max_child_depth)
        {
            max_child_depth = deepest_child_depth[i];
            iDeepest = i;
        }
    }

    cout << max_child_depth + 1 << endl;

    vector<int> chain;
    for (int i = iDeepest; i != -1; i = deepest_child[i])
        chain.push_back(i + 1);

    copy(chain.rbegin(), chain.rend(), ostream_iterator<int>(cout, " "));
}
