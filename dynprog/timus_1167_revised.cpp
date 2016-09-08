// Solution for http://acm.timus.ru/problem.aspx?space=1&num=1167 ("Bicolored Horses")
// O(N^3) time complexity, O(N^2) space complexity.
// This solution is inspired by mekhas's solution of this problem.

#include <limits>
#include <stdio.h>

using namespace std;

const int MAX_N = 500;

long sum[MAX_N];
long r[MAX_N+1][MAX_N+1];

long dis(int i, int j)
{
    long blacks = (j == 0 ? 0 : sum[j-1]) - (i == 0 ? 0 : sum[i-1]);
    return blacks * (j - i - blacks);
}

int main()
{
    int n, k;
    scanf("%d%d", &n, &k);

    long sum_so_far = 0;
    for (int i = 0; i < n; ++i)
    {
        short s;
        scanf("%hd", &s);

        sum_so_far += s;
        sum[i] = sum_so_far;
    }

    for (int i = 1; i <= n; ++i)
        r[i][1] = dis(0, i);

    for (int i = 1; i <= n; ++i)
        for (int j = 2; j <= k; ++j)
        {
            r[i][j] = numeric_limits<long>::max();

            for (int o = j-1; o <= i-1; ++o)
                if (r[o][j-1] + dis(o, i) < r[i][j])
                    r[i][j] = r[o][j-1] + dis(o, i);
        }

    printf("%ld", r[n][k]);
}
