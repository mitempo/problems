// http://acm.timus.ru/problem.aspx?space=1&num=1225

#include <cstdio>
#include <vector>

using namespace std;

int main()
{
    int n;
    scanf("%d", &n);
    
    vector<long long> end_in_r(n + 1);
    vector<long long> end_in_w(n + 1);
    
    end_in_r[1] = 1;
    end_in_w[1] = 1;
    
    for (int i = 2; i <= n; ++i)
    {
        end_in_r[i] = end_in_w[i-1] + end_in_r[i-2];
        end_in_w[i] = end_in_r[i-1] + end_in_w[i-2];
    }
    
    printf("%lld", end_in_r[n] * 2);
}
