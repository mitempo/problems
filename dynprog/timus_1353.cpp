// http://acm.timus.ru/problem.aspx?space=1&num=1353

#include <cstdio>
#include <algorithm>

using namespace std;

long d[1000];

long solve(int s, int maxd)
{
    if (s == 0) return 1;
    if (maxd == 0 || s < 0) return 0;

    long &result = d[s * 10 + maxd];

    if (result < 0)
    {
        result = 0;

        for (int i = 0; i < 10; ++i)
            result += solve(s - i, maxd - 1);
    }

    return result;
}

int main()
{
    int s;
    scanf("%d", &s);

    fill(d, d + sizeof d/sizeof *d, -1);
    long result = solve(s, 9);

    result += s == 1;

    printf("%ld", result);
}
