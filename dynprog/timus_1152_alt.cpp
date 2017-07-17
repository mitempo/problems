// http://acm.timus.ru/problem.aspx?space=1&num=1152

#include <cstdio>
#include <vector>
#include <cstdint>
#include <algorithm>
#include <limits>

using namespace std;

vector<uint32_t> shot_masks;
vector<int> m(1 << 20);
vector<int> d(1 << 20, numeric_limits<int>::max());

int solve(uint32_t state)
{
    if (state == 0) return 0;
    int& r = d[state];
    if (r != numeric_limits<int>::max()) return r;

    for (auto sm : shot_masks)
    {
        uint32_t newstate = state & ~sm;
        if (newstate == state) continue;
        r = min(r, solve(newstate) + m[newstate]);
    }

    return r;
}

int main()
{
    int n;
    scanf("%d", &n);

    vector<int> v(n);

    for (int i = 0; i < n; ++i)
        scanf("%d", &v[i]);

    uint32_t full_mask = (1 << n) - 1;

    for (uint32_t i = 0; i <= full_mask; ++i)
    {
        uint32_t mask = i;
        for (int j = 0; j < n && mask != 0; ++j, mask >>= 1)
            if (mask & 1) m[i] += v[j];
    }

    for (uint32_t shot_mask = 7; shot_masks.size() < n;)
    {
        shot_masks.push_back(shot_mask);
        shot_mask = shot_mask << 1 & full_mask | shot_mask >> (n - 1);
    }

    printf("%d", solve(full_mask));
}
