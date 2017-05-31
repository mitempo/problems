// http://acm.timus.ru/problem.aspx?space=1&num=1228

#include <cstdio>

using namespace std;

int main()
{
    long n, s;

    scanf("%ld %ld", &n, &s);

    while (n--)
    {
        long d;
        scanf("%ld", &d);
        printf("%ld ", s / d - 1); 
        s = d;
    }
}
