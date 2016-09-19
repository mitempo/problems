#include <algorithm>
#include <cstdio>
#include <limits>
#include <cstdint>
#include <vector>

using namespace std;

int n, m, k;

struct item
{
    int cost;
    int power;
};

struct box
{
    int ocost;
    vector<item> items = vector<item>(21);

    bool operator<(const box& other) { return ocost > other.ocost; }
};

box boxes[21];

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

    for (int j = k - boxes[i].ocost; j >= 0; --j)
        maxp = max(maxp, d[i][j] + solverec(i + 1, k - boxes[i].ocost - j));

    return maxp;
}

void solve()
{
    scanf("%d %d %d", &n, &m, &k);

    for (int i = 0; i < n; ++i)
        scanf("%d", &boxes[i].ocost);

    for (int i = 0; i < n; ++i)
    for (int j = 0; j < m; ++j)
        scanf("%d", &boxes[i].items[j].cost);

    for (int i = 0; i < n; ++i)
    for (int j = 0; j < m; ++j)
        scanf("%d", &boxes[i].items[j].power);

    sort(boxes, boxes + n);

    for (int i = 0; i < n; ++i)
        solvebox(&boxes[i].items[0], d[i]);

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
