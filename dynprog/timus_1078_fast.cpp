// Fast solution for http://acm.timus.ru/problem.aspx?space=1&num=1078 ("Segments")

#include <stdio.h>

short startz[501];
short endz[501];
short cur[501];

short children[501][501];
short depth[501];
short deepest_child[501];

short output[501];

short n;

short get_depth(short i)
{
    auto& cached = depth[i];
    if (cached != 0) return cached;

    for (short j = 0; children[i][j] != 0; ++j)
    {
        short depth_candidate = get_depth(children[i][j]);
        if (depth_candidate > cached)
        {
            cached = depth_candidate;
            deepest_child[i] = children[i][j];
        }
    }

    return ++cached;
}

int main()
{
    scanf("%hd", &n);

    for (short i = 1; i <= n; ++i)
        scanf("%hd%hd", startz + i, endz + i);

    // Build DAG

    for (short i = 1; i <= n; ++i)
        for (short j = 1; j <= n; ++j)
            if (startz[i] < startz[j] && endz[i] > endz[j]) children[i][cur[i]++] = j;

    // Find the deepest segment

    short max_depth = 0;
    short deepest = 0;

    for (short i = 1; i <= n; ++i)
    {
        short depth = get_depth(i);
        if (depth > max_depth)
        {
            max_depth = depth;
            deepest = i;
        }
    }

    printf("%hd\n", max_depth);

    short *pnext = output;
    for (short i = deepest; i != 0; i = deepest_child[i])
        *pnext++ = i;

    while (pnext != output)
        printf("%hd ", *--pnext);
}
