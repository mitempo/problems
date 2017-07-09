// Solution for http://acm.timus.ru/problem.aspx?space=1&num=1167 ("Bicolored Horses")
// From scratch, 2017/07/09

#include <cstdio>
#include <algorithm>
#include <limits>

using namespace std;

int hline[501];
int b[501][501];
long long d[501][501];

long long solve(int n, int k)
{
    if (n < 0 || k < 0 || n < k) return numeric_limits<long long>::max() / 2;
    if (n == k) return 0;

    long long& r = d[n][k];

    if (r != -1) return r;

    r = numeric_limits<long long>::max() / 2;

    for (int i = 0; i < n; ++i)
        r = min(r, solve(i, k - 1) + (n - i - b[i][n]) * b[i][n]);

    return r;
}

int main()
{
    int n, k;
    scanf("%d %d", &n, &k);

    for (int i = 0; i < n; ++i)
        scanf("%d", hline + i);

    for (int i = 0; i < n; ++i)
    for (int j = i + 1; j <= n; ++j)
    {
        if (i == 0)
        {
            b[i][j] = b[i][j - 1] + hline[j - 1];
            continue;
        }

        b[i][j] = b[i - 1][j] - hline[i - 1];
    }

    fill_n((long long *)d, 501 * 501, -1);

    printf("%lld", solve(n, k));
}
