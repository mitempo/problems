#include <iostream>

using namespace std;

unsigned long long d[501][501];

unsigned long long f(int n, int min)
{
    if (n < min) return 0;
    if (n == min) return 1;

    if (d[n][min] == 0)
        d[n][min] = f(n, min + 1) + f(n - min, min + 1);

    return d[n][min];
}

int main()
{
    int n;
    cin >> n;
    cout << f(n, 1) - 1;

    #ifdef DEBUG
    for (int i = 0; i < 40; ++i)
    {
        for (int j = 0; j < 40; ++j)
            if (d[i][j] == 0) printf("  ."); else printf("%3llu", d[i][j]);
        cout << endl;
    }
    #endif
}
