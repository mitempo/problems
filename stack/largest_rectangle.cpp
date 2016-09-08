#include <cstdio>
#include <stack>
#include <utility>
#include <cstdint>
#include <algorithm>

using namespace std;

int main()
{
    uint32_t n;
    scanf("%u\n", &n);

    stack<pair<uint32_t,uint32_t>> stk;
    uint32_t s = 0;

    for (uint32_t i = 0; i <= n; ++i)
    {
        uint32_t h;

        if (i < n)
            scanf("%u", &h);
        else
            h = 0;

        uint32_t ilast = (uint32_t)-1;
        while (!stk.empty() && stk.top().first >= h)
        {
            ilast = stk.top().second;
            uint32_t sq = (i - ilast) * stk.top().first;
            if (sq > s) s = sq; 
            stk.pop();
        }

        stk.push({h, min(i, ilast)});
    }

    printf("%u\n", s);
}
