// Solution for http://acm.timus.ru/problem.aspx?space=1&num=1029 ("Ministry")
// Linear algorithm, time complexity O(MxN)

#include <cstdio>
#include <vector>

using namespace std;

using ullong = unsigned long long;

struct nodeid
{
    int i;
    int j;
};

const int MAX_M = 100; // Max possible number of floors
const int MAX_N = 500; // Max possible number of rooms on a floor

ullong input[MAX_M][MAX_N]; // Ministry as read from the input
ullong lens [MAX_M][MAX_N]; // Lengths of the shortest paths
nodeid pred [MAX_M][MAX_N]; // Predecessor rooms on the shortest path

int m; // Number of floors
int n; // Number of rooms on each floor

int main()
{
    scanf("%d%d", &m, &n);

    for (int i = 0; i < m; ++i)
        for (int j = 0; j < n; ++j)
        {
            scanf("%llu", &input[i][j]);
            pred[i][j] = {i-1, j};
        }

    for (int j = 0; j < n; ++j)
        lens[0][j] = input[0][j];

    for (int i = 1; i < m; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            lens[i][j] = lens[i-1][j] + input[i][j];
            pred[i][j] = {i-1, j};
        }


        for (int j = 1; j < n; ++j)
        {
            auto len = lens[i][j-1] + input[i][j];

            if (len < lens[i][j])
            {
                lens[i][j] = len;
                pred[i][j] = {i, j-1};
            }
        }

        for (int j = n - 2; j >= 0; --j)
        {
            auto len = lens[i][j+1] + input[i][j];

            if (len < lens[i][j])
            {
                lens[i][j] = len;
                pred[i][j] = {i, j+1};
            }
        }
    }

    auto len = static_cast<ullong>(-1);
    int col = -1;

    for (int j = 0; j < n; ++j)
    {
        if (lens[m-1][j] < len)
        {
            len = lens[m-1][j];
            col = j;
        }
    }

    vector<int> result;

    nodeid cur = {m-1, col};

    do
    {
        result.push_back(cur.j + 1);
        cur = pred[cur.i][cur.j];
    } while (cur.i >= 0);

    for (auto p = result.rbegin(); p != result.rend(); ++p)
        printf("%d ", *p);
}
