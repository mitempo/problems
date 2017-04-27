// http://acm.timus.ru/problem.aspx?space=1&num=1120
// Sequence sum

#include <cstdio>

using namespace std;

int main()
{
    long long n;
    scanf("%lld", &n);

    long long p = 0;
    long long a = 0;

    for (long long i = 0; i < n; ++i)
    {
        long long triangle = i * (i + 1) / 2;

        if (triangle >= n) break;

        long long d = (n - triangle) / (i + 1);
        long long r = (n - triangle) % (i + 1);

        if (r == 0 && d > 0)
        {
            a = d;
            p = i + 1;
        }
    }

    printf("%lld %lld\n", a, p);
}
