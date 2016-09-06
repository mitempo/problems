#include <iostream>
#include <string>
#include <algorithm>
#include <utility>
#include <tuple>
#include <vector>
#include <set>
#include <map>
#include <limits>

using namespace std;

class solver
{
    using I = string::const_iterator;

    map<tuple<I, I, I, I>, pair<map<char, string>, long>> d;
    map<char, int> f;

    long cost(map<char, string> r)
    {
        long cost = 0;

        for (auto&& e : r)
            for (int i = 0; i < e.second.size(); ++i)
                cost += (i + 1) * f[e.second[i]];

        return cost;
    }

public:
    solver(map<char, int> freq_table) : f(freq_table) {}

    map<char, string> solve(I pkb, I pke, I plb, I ple)
    {
        auto args = make_tuple(pkb, pke, plb, ple);

        auto ps = d.find(args);
        if (ps != d.cend()) return ps->second.first;

        auto r = do_solve(pkb, pke, plb, ple);
        d[args] = make_pair(r, cost(r));

        return r;
    }

private:
    map<char, string> do_solve(I pkb, I pke, I plb, I ple)
    {
        map<char, string> r;

        if (pkb == pke) return r;

        r[*pkb] = string();

        long minsofar = numeric_limits<long>::max();
        map<char, string> nrsofar;

        for (; plb != ple; ++plb)
        {
            r[*pkb] += *plb;

            auto nr = solve(next(pkb), pke, next(plb), ple);

            long cst = cost(r) + cost(nr);

            if (cst < minsofar)
            {
                minsofar = cst;
                nrsofar = nr;
            }
        }

        r.insert(nrsofar.cbegin(), nrsofar.cend());
        return r;
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

        for (auto&& pair : solver(freq_table).solve(keys.cbegin(), keys.cend(), letters.cbegin(), letters.cend()))
            cout << pair.first << ": " << pair.second << endl;
    }
}
