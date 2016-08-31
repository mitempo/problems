#include <iostream>

using namespace std;

unsigned long long d[501][501];

unsigned long long f(int n, int min)
{
    if (n == 0) return 1;

    if (d[n][min] != 0) return d[n][min];

    for (int i = min + 1; i <= n; ++i)
        d[n][min] += f(n - i, i);

    return d[n][min];
}

int main()
{
    int n;
    cin >> n;
    cout << f(n, 0) - 1;

    #ifdef DEBUG
    for (int i = 0; i < 40; ++i)
    {
        for (int j = 0; j < 40; ++j)
            if (d[i][j] == 0) printf("  ."); else printf("%3llu", d[i][j]);
        cout << endl;
    }
    #endif
}
