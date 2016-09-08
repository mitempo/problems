#include <assert.h>
#include <stdio.h>

int fib[2][50];
char result[50];

int main()
{
    int n;
    int k;

    scanf("%d%d", &n, &k);

    assert(n > 0);
    assert(n < 44);
    assert(k >= 0);
    assert(k < 1000000000);

    fib[0][1] = 1;
    fib[1][1] = 1;

    for (int i = 2; i <= n; ++i)
    {
        fib[0][i] = fib[0][i-1] + fib[1][i-1];
        fib[1][i] = fib[0][i-1];
    }

    if (k > fib[0][n] + fib[1][n])
    {
        puts("-1");
        return 0;
    }

    char *p = result;

    for (int i = n; i > 0; --i)
    {
        if (k <= fib[0][i])
        {
            *p++ = '0';
        }
        else
        {
            *p++ = '1';
            k -= fib[0][i];
        }
    }

    puts(result);
}
