// http://www.spoj.com/problems/PIGBANK

#include <cstdio>
#include <limits>
#include <algorithm>
#include <type_traits>

using namespace std;

const int pinf = numeric_limits<int>::max() / 2;
int e, f, n;

int p[1000];
int w[1000];

int d[20000];

void init()
{
    scanf("%d %d\n%d\n", &e, &f, &n);

    for (int i = 0; i < n; ++i)
        scanf("%d %d\n", p + i, w + i);

    fill_n(d, extent<decltype(d), 0>::value, -1);
}

int solve(int weight)
{
    if (weight < 0) return pinf;
    if (weight == 0) return 0;

    if (d[weight] != -1) return d[weight];

    d[weight] = pinf;

    for (int i = 0; i < n; ++i)
        d[weight] = min(d[weight], p[i] + solve(weight - w[i]));

    return d[weight];
}

int main()
{
    int t;
    scanf("%d\n", &t);

    while (t--)
    {
        init();
        int r = solve(f - e);

        if (r < pinf)
            printf("The minimum amount of money in the piggy-bank is %d.\n", r);
        else
            printf("This is impossible.\n");
    }
}
