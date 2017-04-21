// Factorials
// http://acm.timus.ru/problem.aspx?space=1&num=1083

#include <cstdio>
#include <cstring>

using namespace std;

int main()
{
    int n;
    char excls[100];
    scanf("%d %s", &n, excls);
    
    int k = strlen(excls);

    long long result = 1;
    while (n > 0)
    {
        result *= n;
        n -= k;
    }

    printf("%lld", result);    
}
