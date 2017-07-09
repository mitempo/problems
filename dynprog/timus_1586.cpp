// http://acm.timus.ru/problem.aspx?space=1&num=1586

#include <cstdio>
#include <algorithm>
#include <cassert>

using namespace std;

bool is_compo[1000];

long long cnt[100];
long long cnt_next[100];

long long normalize(long long& l)
{
    l %= 1000000009;
    return l;
}

void inc(long long& l)
{
    ++l;
    if (l & 0xFF00000000000000) normalize(l);
}

void add(long long& l1, long long l2)
{
    l1 += l2;
    normalize(l1);
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
    scanf("%d", &n);

    assert(n >= 3 && n <= 10000);

    for (int i = 0; i < 1000; ++i)
        if (is_3prime(i))
            inc(cnt[i % 100]);

    for (int i = 4; i <= n; ++i)
    {
        for (int j = 11; j < 100; ++j)
        {
            if (cnt[j] == 0) continue;

            for (int k : {1, 3, 7, 9})
            {
                int candidate = j % 100 * 10 + k;
                if (!is_3prime(candidate)) continue;
                add(cnt_next[candidate % 100], cnt[j]);
            }
        }

        copy(cnt_next, cnt_next + 100, cnt);
        fill_n(cnt_next, 100, 0);
    }

    long long s = 0;
    for (int i = 0; i < 100; ++i)
        add(s, cnt[i]);

    printf("%lld", normalize(s));
}
