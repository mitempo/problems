#include <cstdio>

using namespace std;

long solve(int n)
{
    n -= 3;
    if (n < 0) return 1;

    long a = 0;
    long c = 1;
    long d = 0;
    long e = 1;

    while (n--)
    {
        a += c;
        long dp = c;
        c = e;
        e += d;
        d = dp;
    }

    return a + c + d + e;
}

int main()
{
    int n;
    scanf("%d", &n);
    printf("%ld", solve(n));
}
