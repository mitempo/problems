// Solution for http://acm.timus.ru/problem.aspx?space=1&num=1146 ("Maximum Sum")

#include <stdio.h>
#include <algorithm>
#include <limits>

using namespace std;

const size_t MAX_N = 100;

int s[MAX_N][MAX_N];

int main()
{
    size_t n;
    scanf("%u", &n);

    for (size_t i = 0; i < n; ++i)
    for (size_t j = 0; j < n; ++j)
    {
        int value;
        scanf("%d", &value);
        s[i][j] = (i == 0 ? 0 : s[i-1][j]) + value;
    }

    int globalmax = numeric_limits<int>::min();

    for (size_t i = 0; i < n; ++i)
    for (size_t k = i; k < n; ++k)
    {
        int maxcol = numeric_limits<int>::min();
        int maxsofar = 0;
        int maxendinghere = 0;

        for (size_t j = 0; j < n; ++j)
        {
            int col = s[k][j] - (i == 0 ? 0 : s[i-1][j]);
            maxcol = max(maxcol, col);
            maxendinghere = max(maxendinghere + col, 0);
            maxsofar = max(maxsofar, maxendinghere);
        }

        globalmax = max(globalmax, maxcol < 0 ? maxcol : maxsofar);
    }

    printf("%d", globalmax);
}
