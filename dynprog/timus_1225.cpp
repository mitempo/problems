// http://acm.timus.ru/problem.aspx?space=1&num=1225

#include <cstdio>

using namespace std;

int main()
{
    int n;
    scanf("%d", &n);
    
    long long a = 0;
    long long b = 2;

    for (int i = 2; i <= n; ++i)
    {
        long long new_b = b + a;
        a = b;
        b = new_b;
    }

    printf("%lld", b);
}
