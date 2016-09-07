// Solution for http://acm.timus.ru/problem.aspx?space=1&num=1167 ("Bicolored Horses")
// Yet another solution, written from scratch 1.5 years after the previous one.
// Actually, threeo solutions: forward, backward and iterative.

#include <iostream>
#include <type_traits>
#include <algorithm>
#include <vector>
#include <limits>
#include <memory>

using namespace std;

class solver
{
private:
    const static int maxn = 501;

    long cost[maxn][maxn];
    long d[maxn][maxn];
    vector<bool> colors;
    size_t n;
    size_t k;

public:
    solver(const vector<bool>& colors, size_t k) : colors(colors), k(k)
    {
        n = colors.size();
        /*
        fill_n(
            (remove_all_extents<decltype(d)>::type *)d,
            extent<decltype(d), 0>::value * extent<decltype(d), 1>::value,
            -1);
        */

        for (size_t i = 0; i < n; ++i)
        {
            long b = 0;
            long w = 0;

            for (size_t j = i + 1; j <= n; ++j)
            {
                if (colors[j-1]) ++b; else ++w;
                cost[i][j] = b * w;
            }
        }
    }

    long solve(size_t ik, size_t in)
    {
        long& r = d[ik][in];
        if (r != -1) return r;

        r = numeric_limits<long>::max() / 2;

        if (ik == k)
            return r = in == n ? 0 : r;

        for (auto iend = in + 1; iend <= n; ++iend)
            r = min(r, cost[in][iend] + solve(ik + 1, iend));

        return r;
    }

    long solve_back(int ik, int in)
    {
        if (ik == 0 && in == 0) return 0;
        if (ik == 0 || in == 0) return numeric_limits<long>::max() / 2;

        long& r = d[ik][in];
        if (r != -1) return r;

        r = numeric_limits<long>::max() / 2;

        for (int ibeg = in - 1; ibeg >= 0; --ibeg)
            r = min(r, cost[ibeg][in] + solve_back(ik - 1, ibeg));

        return r;
    }

    long solve_iterative()
    {
        for (int i = 0; i <= k; ++i)
            for (int j = 0; j <= n; ++j)
                if (j == i)
                    d[i][j] = 0;
                else
                {
                    d[i][j] = numeric_limits<long>::max() / 2;
                    if (i == 0 || j < i) continue;
                    for (int l = 0; l < j; ++l)
                        d[i][j] = min(d[i][j], d[i-1][l] + cost[l][j]);
                }

        return d[k][n];
    }
};

int main()
{
    size_t n, k;
    cin >> n >> k;

    vector<bool> colors(n);

    for (size_t i = 0; i < n; ++i)
    {
        size_t color;
        cin >> color;
        colors[i] = color != 0; 
    }

    cout << make_unique<solver>(colors, k)->solve_iterative();
}
