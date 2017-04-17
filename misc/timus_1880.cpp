// Team's eigenvalues
// http://acm.timus.ru/problem.aspx?space=1&num=1880

#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    vector<vector<long long>> vecs(3);
    
    for (auto&& v : vecs)
    {
        int len;
        scanf("%d", &len);
        
        while (len-- > 0)
        {
            long long l;
            scanf("%lld", &l);
            v.push_back(l);
        }
    }
    
    int i[3] = {0, 0, 0};
    int count = 0;

    while (i[0] < vecs[0].size() && i[1] < vecs[1].size() && i[2] < vecs[2].size())
    {
        if (vecs[0][i[0]] == vecs[1][i[1]] && vecs[1][i[1]] == vecs[2][i[2]])
        {
            ++count;
            ++i[0];
            ++i[1];
            ++i[2];
            continue;
        }
        
        int mini = vecs[0][i[0]] < vecs[1][i[1]] ? 0 : 1;
        mini = vecs[2][i[2]] < vecs[mini][i[mini]] ? 2 : mini;
        ++i[mini];
    }

    printf("%d", count);
}
