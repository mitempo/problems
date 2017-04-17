#include <algorithm>
#include <cstdio>

using namespace std;

int main()
{
    unsigned n;
    scanf("%u", &n);

    unsigned v[100];

    for (unsigned i = 0; i < n; ++i)
        scanf("%u", v + i);

    sort(v, v + n);

    for (unsigned i = 0; i < n; ++i)
        printf("%u\n", v[i]);
}
