#include <iostream>
#include <string>
#include <utility>
#include <tuple>
#include <vector>
#include <map>
#include <limits>
#include <numeric>

using namespace std;

class solver
{
    using I = string::const_iterator;

    map<tuple<I, I, I, I>, pair<map<char, string>, long>> d;
    map<char, int> f;

    long cost(string s)
    {
        long cost = 0;

        for (int i = 0; i < s.size(); ++i)
            cost += (i + 1) * f[s[i]];

        return cost;
    }

    long cost(map<char, string> r)
    {
        return accumulate(r.cbegin(), r.cend(), 0, [&](long acc, pair<char, string> e){ return acc + cost(e.second); });
    }

public:
    solver(map<char, int> freq_table) : f(freq_table) {}

    pair<map<char, string>, long> solve(I pkb, I pke, I plb, I ple)
    {
        auto args = make_tuple(pkb, pke, plb, ple);

        auto ps = d.find(args);
        if (ps != d.cend()) return ps->second;

        return d[args] = do_solve(pkb, pke, plb, ple);
    }

private:
    pair<map<char, string>, long> do_solve(I pkb, I pke, I plb, I ple)
    {
        map<char, string> r;
        long mincost = plb == ple ? 0 : numeric_limits<long>::max() / 2;

        if (pkb == pke) return {r, mincost};

        string s;

        for (; plb != ple; ++plb)
        {
            s += *plb;

            auto nr = solve(next(pkb), pke, next(plb), ple);
            long cst = cost(s) + nr.second;

            if (cst < mincost)
            {
                mincost = cst;
                r = nr.first;
                r[*pkb] = s;
            }
        }

        return {r, mincost};
    }
};

int main()
{
    int t;
    cin >> t;

    for (int i = 0; i < t; ++i)
    {
        int k, l;
        cin >> k >> l;

        string keys, letters;
        cin >> keys >> letters;

        vector<int> f{istream_iterator<int>(cin), istream_iterator<int>()};

        map<char, int> freq_table;

        for (int j = 0; j < l; ++j)
            freq_table[letters[j]] = f[j];

        cout << "Keypad #" << (i + 1) << ":" << endl;

        for (auto&& pair : solver(freq_table).solve(keys.cbegin(), keys.cend(), letters.cbegin(), letters.cend()).first)
            cout << pair.first << ": " << pair.second << endl;
    }
}
