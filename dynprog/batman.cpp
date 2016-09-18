#include <algorithm>
#include <cstdio>
#include <limits>
#include <cstdint>

using namespace std;

int n, m, k;

struct item
{
    int cost;
    int power;

    bool operator<(const item& other) { return cost > other.cost; }
};

int ocost[21];
item items[21][21];

int d[21][1001];

void solvebox(item *itemz, int *dbox)
{
    for (int i = 0; i <= k; ++i)
    {
        dbox[i] = 0;

        for (int j = 0; j < m; ++j)
            if (i - itemz[j].cost >= 0)
                dbox[i] = max(dbox[i], itemz[j].power + dbox[i - itemz[j].cost]);
    }
}

int solverec(int i, int k)
{
    if (i >= n || k <= 0) return 0;

    int maxp = solverec(i + 1, k);

    for (int j = k - ocost[i]; j >= 0; --j)
        maxp = max(maxp, d[i][j] + solverec(i + 1, k - ocost[i] - j));

    return maxp;
}

void solve()
{
    scanf("%d %d %d", &n, &m, &k);

    for (int i = 0; i < n; ++i)
        scanf("%d", ocost + i);

    for (int i = 0; i < n; ++i)
    for (int j = 0; j < m; ++j)
        scanf("%d", &items[i][j].cost);

    for (int i = 0; i < n; ++i)
    for (int j = 0; j < m; ++j)
        scanf("%d", &items[i][j].power);

    for (int i = 0; i < n; ++i)
    {
        sort(items[i], items[i] + n);
        solvebox(items[i], d[i]);
    }

    printf("%d\n", solverec(0, k));
}

int main()
{
    int t;
    scanf("%d", &t);

    while (t--)
    {
        solve();
    }
}
