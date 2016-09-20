#include <algorithm>
#include <cstdio>
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
};

box boxes[21];

int d[21][1001];
int outerd[21][1001];

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

void solve_outer()
{
    fill(outerd[0], outerd[0] + boxes[0].ocost, 0);

    if (boxes[0].ocost < k)
        copy(d[0], d[0] + k + 1 - boxes[0].ocost, outerd[0] + boxes[0].ocost);

    for (int i = 1; i < n; ++i)
    {
        for (int l = 0; l <= k; ++l)
        {
            outerd[i][l] = outerd[i - 1][l];

            for (int j = l - boxes[i].ocost; j >= 0; --j)
                outerd[i][l] = max(outerd[i][l], d[i][j] + outerd[i-1][l - boxes[i].ocost - j]);
        }
    }
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

    for (int i = 0; i < n; ++i)
        solvebox(&boxes[i].items[0], d[i]);

    solve_outer();
    printf("%d\n", outerd[n-1][k]);
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
