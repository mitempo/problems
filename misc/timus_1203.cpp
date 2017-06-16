// http://acm.timus.ru/problem.aspx?space=1&num=1203

#include <cstdio>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

int main()
{
    long n;
    scanf("%ld", &n);
    vector<pair<int, int>> v;

    while (n--)
    {
        int ts, te;
        scanf("%d %d", &ts, &te);
        v.emplace_back(ts, te);
    }

    sort(v.begin(), v.end(), [](const auto& p1, const auto& p2){ return p1.second < p2.second; });

    long c = 0;
    int t = -1;
    auto p = v.cbegin();

    for ( ; ; )
    {
        p = find_if(p, v.cend(), [t](const auto& e){ return e.first > t; });

        if (p == v.cend()) break;

        ++c;
        t = p++->second;
    }

    printf("%ld", c);
}
