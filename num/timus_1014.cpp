#include <cstdio>
#include <set>

using namespace std;

int main()
{
    long n;
    scanf("%ld", &n);

    if (n == 0)
    {
        printf("10");
        return 0;
    }

    multiset<int> digits;

    for (int d = 9; d > 1; --d)
    {
        for ( ; ; )
        {
            int r = n % d;

            if (r != 0) break;

            digits.insert(d);
            n /= d;
        }
    }

    if (n != 1)
        printf("-1");
    else if (digits.empty())
        printf("1");
    else
        for (int d : digits)
            printf("%d", d);
}
