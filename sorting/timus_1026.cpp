// http://acm.timus.ru/problem.aspx?space=1&num=1026

#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    int n;
    vector<int> v;
    
    scanf("%d", &n);
    v.reserve(n);
    
    while (n--)
    {
        int e;
        scanf("%d", &e);
        v.push_back(e);
    }
    
    sort(v.begin(), v.end());
    
    scanf("%*s%d", &n);

    while (n--)
    {
        int i;
        scanf("%d", &i);
        printf("%d\n", v[i-1]);
    }
}
