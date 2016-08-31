// A new solution, developed from scratch

#include <algorithm>
#include <iostream>

using namespace std;

const int MAXN = 501;
long long s[MAXN][MAXN];

// Number of stairs of n blocks with the highest column
// is no larger than k.
auto stairs(int n, int k) -> long long
{
    if (n < 0 || k < 0) return 0LL;

    auto& v = s[n][k];
    return v != -1 ? v : (v = stairs(n, k-1) + stairs(n-k, k-1));
}

int main()
{
    fill((long long*)s, (long long*)s+MAXN*MAXN, -1);
    s[0][0] = 1;

    int n;
    cin >> n;

    cout << stairs(n, n) - 1;

    #ifdef DEBUG
    for (int i = 0; i < 40; ++i)
    {
        for (int j = 0; j < 40; ++j)
            if (s[i][j] == 0 || s[i][j] == -1) printf("  ."); else printf("%3llu", s[i][j]);
        cout << endl;
    }
    #endif
}
