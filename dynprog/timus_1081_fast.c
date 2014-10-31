// Fast solution for http://acm.timus.ru/problem.aspx?space=1&num=1081 ("Binary Lexicographic Sequence")

#include <assert.h>
#include <stdio.h>

int fib[45];
char result[45];

int main()
{
    int n;
    int k;

    scanf("%d%d", &n, &k);

    assert(n > 0);
    assert(n < 44);
    assert(k >= 0);
    assert(k < 1000000000);

    int a = fib[0] = 1;
    int b = 1;

    for (int i = 1; i <= n; ++i)
    {
        int temp = b;
        b += a;
        a = fib[i] = temp;
    }

    if (k > fib[n] + fib[n-1])
    {
        puts("-1");
        return 0;
    }

    char *p = result;

    for (int i = n; i > 0; --i)
    {
        if (k <= fib[i])
        {
            *p++ = '0';
        }
        else
        {
            *p++ = '1';
            k -= fib[i];
        }
    }

    puts(result);
}
