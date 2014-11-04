// Solution for http://acm.timus.ru/problem.aspx?space=1&num=1029 ("Ministry")

#include <algorithm>
#include <iostream>
#include <iterator>
#include <limits>
#include <vector>

using namespace std;

const int MAX_M = 100; // Max number of floors
const int MAX_N = 500; // Max number of rooms on a floor

long long input[MAX_M][MAX_N];
int starts[MAX_M][MAX_N];       // Each element is the index of starting point within the same layer on the shortest path towards the given end point.
long long lens[MAX_M][MAX_N];   // Each element is the lengths of shortest paths towards the given end point.

int main()
{
    int m; // Number of floors
    int n; // Number of rooms on each floor;

    cin >> m >> n;

    for (int i = 0; i < m; ++i)
        for (int j = 0; j < n; ++j)
            cin >> input[i][j];

    for (int j = 0; j < n; ++j)
    {
        starts[0][j] = j;
        lens[0][j] = input[0][j];
    }

    for (int i = 1; i < m; ++i)
    {
        const long long *rooms = input[i];

        // Calculate path lengths between all the pairs of rooms on floor i
        long long paths_within_level[MAX_N][MAX_N];
        paths_within_level[0][0] = rooms[0];
        for (int j = 1; j < n; ++j)
        {
            paths_within_level[0][j] = paths_within_level[j][0] = paths_within_level[0][j-1] + rooms[j];
            paths_within_level[j][j] = rooms[j];
            for (int k = 1; k < j; ++k)
                paths_within_level[k][j] = paths_within_level[j][k] = paths_within_level[k-1][j] - rooms[k-1];
        }

        for (int j = 0; j < n; ++j)
        {
            lens[i][j] = numeric_limits<decltype(j)>::max();
            starts[i][j] = -1;

            for (int k = 0; k < n; ++k)
            {
                long long path_to_j_via_k = lens[i-1][k] + paths_within_level[k][j];
                if (path_to_j_via_k < lens[i][j])
                {
                    lens[i][j] = path_to_j_via_k;
                    starts[i][j] = k;
                }
            }
        }
    }

    long long min_path = numeric_limits<long>::max();
    int last = -1;

    for (int j = 0; j < n; ++j)
        if (lens[m-1][j] < min_path)
        {
            min_path = lens[m-1][j];
            last = j;
        }

    vector<int> result;
    for (int i = m-1; i >= 0; --i)
    {
        int step = (starts[i][last] > last) * 2 - 1;
        for (int j = last; j != starts[i][last] + step; j += step)
            result.push_back(j + 1);
        last = starts[i][last];
    }

    copy(result.rbegin(), result.rend(), ostream_iterator<int>(cout, " "));
}
