// Solution for http://acm.timus.ru/problem.aspx?space=1&num=1029 ("Ministry")

#include <algorithm>
#include <iostream>
#include <iterator>
#include <limits>
#include <vector>

using namespace std;

const short MAX_M = 100; // Max possible number of floors
const short MAX_N = 500; // Max possible number of rooms on a floor

long long input  [MAX_M][MAX_N]; // The configuration of the ministry as read from the input
long long lengths[MAX_M][MAX_N]; // Each element is the length of shortest path from the bottom to the given room
short     entry  [MAX_M][MAX_N]; // Each element is the number of the room where the shortest path to the given room enters the room's floor

int main()
{
    short m; // Number of floors
    short n; // Number of rooms on each floor

    cin >> m >> n;

    for (short i = 0; i < m; ++i)
        for (short j = 0; j < n; ++j)
            cin >> input[i][j];

    for (short j = 0; j < n; ++j)
    {
        entry[0][j] = j;
        lengths[0][j] = input[0][j];
    }

    for (short i = 1; i < m; ++i)
    {
        const long long *rooms = input[i];
        const long long *prev_lengths = lengths[i-1];

        // Calculate path lengths between all the pairs of rooms on floor i
        long long infloor[MAX_N][MAX_N];
        infloor[0][0] = rooms[0];
        for (short j = 1; j < n; ++j)
        {
            infloor[j][0] = infloor[j-1][0] + rooms[j];
            infloor[j][j] = rooms[j];
            for (short k = 1; k < j; ++k)
                infloor[j][k] = infloor[j][k-1] - rooms[k-1];
        }

        for (short j = 0; j < n; ++j)
        {
            long long shortest_path = numeric_limits<long long>::max(); // Length of the shortest path from the bottom to (i,j)
            short entry_room = -1;                                      // Number of the room where the shortest path to (i,j) enters floor i

            for (short k = 0; k < n; ++k)
            {
                long long path_to_j_via_k = prev_lengths[k] + (k > j ? infloor[k][j] : infloor[j][k]);
                if (path_to_j_via_k < shortest_path)
                {
                    shortest_path = path_to_j_via_k;
                    entry_room = k;
                }
            }

            lengths[i][j] = shortest_path;
            entry[i][j] = entry_room;
        }
    }

    long long shortest_path = numeric_limits<long long>::max(); // Length of the shortest path from the bottom to the top
    short exit_room = -1;                                       // Number of the room where the shortest path ends

    for (short j = 0; j < n; ++j)
        if (lengths[m-1][j] < shortest_path)
        {
            shortest_path = lengths[m-1][j];
            exit_room = j;
        }

    vector<short> result;
    for (short i = m-1; i >= 0; --i)
    {
        short step = entry[i][exit_room] > exit_room ? 1 : - 1;
        for (short j = exit_room; j != entry[i][exit_room] + step; j += step)
            result.push_back(j + 1);
        exit_room = entry[i][exit_room];
    }

    copy(result.rbegin(), result.rend(), ostream_iterator<short>(cout, " "));
}
