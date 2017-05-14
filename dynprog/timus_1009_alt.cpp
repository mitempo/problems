// Solution for http://acm.timus.ru/problem.aspx?space=1&num=1009

#include <cstdio>

using namespace std;

int main()
{
    long n, k;
    scanf("%d %d", &n, &k);
    
    long a = 0;
    long b = 1;
    
    while (n--)
    {
        auto t = (b + a) * (k-1);
        a = b;
        b = t;
    }
    
    printf("%d", b);
}
