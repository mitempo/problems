#include <algorithm>
#include <cstdio>

using namespace std;

template <typename RAI> void quicksort(RAI first, RAI last)
{
    if (last - first <= 1) return;

    auto pivot = last[-1];
    auto left = first;
    auto right = last - 1;

    for ( ; ; )
    {
        while (left != right && *left < pivot) ++left;
        while (left != right && *right >= pivot) --right;

        if (left == right) break;

        iter_swap(left, right);
    }

    iter_swap(left, last - 1);

    quicksort(first, left);
    quicksort(left + 1, last);
}

int main()
{
    unsigned n;
    scanf("%u", &n);

    unsigned v[100];

    for (unsigned i = 0; i < n; ++i)
        scanf("%u", v + i);

    quicksort(v, v + n);

    for (unsigned i = 0; i < n; ++i)
        printf("%u\n", v[i]);
}
