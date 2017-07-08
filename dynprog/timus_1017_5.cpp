// Developed from scratch a couple of years later, 2017/07/06

#include <cstdio>
#include <algorithm>

using namespace std;

long long d[501][501];

long long solve(int n, int m)
{
    long long &r = d[n][m];

    if (r != -1) return r;

    if (n < m) return r = 0;

    r = 1;
    for (int i = m; i <= n; ++i)
        r += solve(n - i, i + 1);

    return r;
}

int main()
{
    fill_n((long long *)d, 501 * 501, -1);

    int n;
    scanf("%d", &n);

    printf("%lld", solve(n, 1) - 1);
}
