// http://acm.timus.ru/problem.aspx?space=1&num=1586

#include <iostream>
#include <algorithm>
#include <cassert>
#include <cstdint>
#include <numeric>

using namespace std;

bool is_compo[1000];

uint32_t cnt[100];
uint32_t cnt_next[100];

uint32_t add(uint32_t l1, uint32_t l2)
{
    return (l1 + l2) % 1000000009;
}

bool is_3prime(int i)
{
    return i > 99 && !is_compo[i];
}

int main()
{
    for (int i = 2; i <= 32; ++i)
        if (!is_compo[i])
            for (int j = i * 2; j < 1000; j += i)
                is_compo[j] = true;

    int n;
    cin >> n;

    assert(n >= 3 && n <= 10000);

    for (int i = 0; i < 1000; ++i)
        if (is_3prime(i))
            cnt[i % 100] = add(cnt[i % 100], 1);

    for (int i = 4; i <= n; ++i)
    {
        for (int j = 11; j < 100; ++j)
        {
            if (cnt[j] == 0) continue;

            for (int k : {1, 3, 7, 9})
            {
                int candidate = j % 100 * 10 + k;
                if (!is_3prime(candidate)) continue;
                cnt_next[candidate % 100] = add(cnt_next[candidate % 100], cnt[j]);
            }
        }

        copy(cnt_next, cnt_next + 100, cnt);
        fill_n(cnt_next, 100, 0);
    }

    cout << accumulate(cnt, cnt + 100, 0, add);
}
