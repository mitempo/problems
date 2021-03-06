#include <string>
#include <utility>
#include <vector>
#include <limits>
#include <cstdint>
#include <cstring>
#include <type_traits>
#include <cstdio>

using namespace std;

class solver
{
private:
    size_t nkeys;
    const char *l;
    const int *f;

    pair<uint8_t, int32_t> d[100][100];
    int32_t cost[100][100];

public:
    solver(size_t nkeys, const char *letters, const int *freq_table) : nkeys(nkeys), l(letters), f(freq_table)
    {
        for (int i = 0; i < strlen(l); ++i)
        {
            cost[i][i] = 0;

            for (int j = i + 1; j <= strlen(l); ++j)
                cost[i][j] = cost[i][j - 1] + (j - i) * f[l[j - 1]];
        }
    }

    pair<uint8_t, int32_t> solve_(uint8_t ik, uint8_t il)
    {
        auto& r = d[ik][il];
        if (r.first != 0) return r;

        r.second = l[il] == 0 ? 0 : numeric_limits<int32_t>::max() / 2;

        if (ik == nkeys) return r;

        for (uint8_t ib = il; l[ib++] != 0;)
        {
            auto nr = solve_(ik + 1, ib);
            int32_t cst = cost[il][ib] + nr.second;

            if (cst < r.second)
            {
                r.second = cst;
                r.first = ib - il;
            }
        }

        return r;
    }

    vector<string> solve()
    {
        solve_(0, 0);

        vector<string> v(nkeys);

        for (int ik = 0, il = 0; ik < nkeys; ++ik)
        {
            auto newil = il + d[ik][il].first;
            v[ik] = string(l + il, l + newil);
            il = newil;
        }

        return v;
    }
};

int main()
{
    int t;
    scanf("%d", &t);

    for (int i = 1; i <= t; ++i)
    {
        int k, l;
        scanf("%d%d\n", &k, &l);

        char keys[100], letters[100];
        scanf("%s\n", keys);
        scanf("%s\n", letters);

        int f[256];

        for (int j = 0; j < l; ++j)
        {
            int v;
            scanf("%d\n", &v);
            f[letters[j]] = v;
        }

        printf("Keypad #%d:\n", i);

        vector<string> solution = solver(strlen(keys), letters, f).solve();

        for (size_t i = 0; i < solution.size(); ++i)
            printf("%c: %s\n", keys[i], solution[i].c_str());

        printf("\n");
    }
}
