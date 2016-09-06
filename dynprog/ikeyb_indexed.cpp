#include <iostream>
#include <iterator>
#include <string>
#include <utility>
#include <vector>
#include <map>
#include <limits>
#include <numeric>
#include <cstdint>

using namespace std;

class solver
{
    size_t nkeys;
    const char *l;
    map<char, int> f;

    map<uint16_t, pair<vector<uint16_t>, long>> d;

    long cost(uint8_t ib, uint8_t ie)
    {
        long cost = 0;

        for (int w = 1; ib != ie; ++w, ++ib)
            cost += w * f[l[ib]];

        return cost;
    }

public:
    solver(size_t nkeys, const char *letters, map<char, int> freq_table) : nkeys(nkeys), l(letters), f(freq_table) {}

    pair<vector<uint16_t>, long> solve(uint8_t ik, uint8_t il)
    {
        auto args = uint16_t(ik << 8 | il);

        auto ps = d.find(args);
        if (ps != d.cend()) return ps->second;

        return d[args] = do_solve(ik, il);
    }

private:
    pair<vector<uint16_t>, long> do_solve(uint8_t ik, uint8_t il)
    {
        vector<uint16_t> r(nkeys);
        long mincost = l[il] == 0 ? 0 : numeric_limits<long>::max() / 2;

        if (ik == nkeys) return {r, mincost};

        for (uint8_t ib = il; l[ib++] != 0;)
        {
            auto nr = solve(uint8_t(ik + 1), uint8_t(ib));
            long cst = cost(il, ib) + nr.second;

            if (cst < mincost)
            {
                mincost = cst;
                r = nr.first;
                r[ik] = uint16_t(il << 8 | ib);
            }
        }

        return {r, mincost};
    }
};

int main()
{
    int t;
    cin >> t;

    for (int i = 1; i <= t; ++i)
    {
        int k, l;
        cin >> k >> l;

        string keys, letters;
        cin >> keys >> letters;

        map<char, int> f;

        for (int j = 0; j < l; ++j)
        {
            int v;
            cin >> v;
            f[letters[j]] = v;
        }

        cout << "Keypad #" << i << ":" << endl;

        vector<uint16_t> solution = solver(keys.size(), letters.c_str(), f).solve(0, 0).first;

        for (int i = 0; i < solution.size(); ++i)
            cout << keys[i] << ": " << string(letters.c_str() + (solution[i] >> 8), letters.c_str() + (solution[i] & 255)) << endl;

        cout << endl;
    }
}
