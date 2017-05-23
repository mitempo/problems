// http://acm.timus.ru/problem.aspx?space=1&num=1225

#include <cstdio>
#include <vector>

using namespace std;

int main()
{
    int n;
    scanf("%d", &n);
    
    vector<long long> d(n + 1);

    d[1] = 2;

    for (int i = 2; i <= n; ++i)
        d[i] = d[i-1] + d[i-2];

    printf("%lld", d[n]);
}
