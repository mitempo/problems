// Solution for http://acm.timus.ru/problem.aspx?space=1&num=1167 ("Bicolored Horses")
// O(N^3) time complexity, O(N^2) space complexity.

#include <algorithm>
#include <limits>
#include <stdio.h>

using namespace std;

const int MAX_N = 501;

int input[MAX_N];      // Horses' colors
long b[MAX_N][MAX_N];  // Number of black horses in [i,j] range
long d[MAX_N][MAX_N];  // Dissatisfaction for [i,j] range
long r[MAX_N][MAX_N];  // Solution for putting first i horses into j stables.

int main()
{
    int n; // Number of horses
    int k; // Number of stables

    scanf("%d%d", &n, &k);

    for (int i = 1; i <= n; ++i)
    {
        scanf("%d", input + i);
        b[1][i] = b[1][i-1] + input[i];
        d[1][i] = b[1][i] * (i - b[1][i]);
    }

    for (int i = 2; i <= n; ++i)
        for (int j = i; j <= n; ++j)
        {
            b[i][j] = b[i-1][j] - b[i-1][i-1];
            d[i][j] = b[i][j] * (j - i + 1 - b[i][j]);
        }

    for (int i = 1; i <= n; ++i)
        r[i][1] = d[1][i];

    for (int i = 2; i <= n; ++i)
        for (int j = 2; j <= min(i,k); ++j)
        {
            r[i][j] = numeric_limits<long>::max();

            for (int o = j - 1; o <= i - 1; ++o)
            {
                if (r[o][j-1] + d[o+1][i] < r[i][j])
                    r[i][j] = r[o][j-1] + d[o+1][i];
            }
        }

    printf("%lu", r[n][k]);
}
