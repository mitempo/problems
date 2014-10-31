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

        if (start > end) swap(start, end); // Just in case
        segments.push_back({start, end});
    }

    map<pair<int, bool>, set<int>> index; // Maps a {coordinate, is_end} to numbers of all the segments
                                          // starting (if the flag is false) or ending (if the flag is true)
                                          // at that coordinate. NB: It's important that false < true.

    for (int i = 0; i < segments.size(); ++i)
    {
        index[{segments[i].first, false}].insert(i);
        index[{segments[i].second, true}].insert(i);
    }

    vector<unsigned> deepest_child_depth(n);
    vector<int> deepest_child(n, -1);
    vector<set<int>> parent_candidates(n);
    set<int> active;

    for (const auto& e : index)
    {
        if (!e.first.second) // An entry with e.second containing the list of segments starting at e.first.first
        {
            for (int i : e.second)
                parent_candidates[i] = active;

            active.insert(e.second.cbegin(), e.second.cend());
        }
        else // An entry with e.second containing the list of segments ending at e.first.first
        {
            for (int i : e.second) // Elements ending at e.first.first
            {
                unsigned this_depth = deepest_child_depth[i] + 1;

                for (int j : parent_candidates[i])
                {
                    if (segments[j].second == segments[i].second) continue;

                    if (this_depth > deepest_child_depth[j])
                    {
                        deepest_child_depth[j] = this_depth;
                        deepest_child[j] = i;
                    }
                }

                active.erase(i);
            }
        }
    }

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
