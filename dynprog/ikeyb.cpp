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

    map<char, string> do_solve(I pkb, I pke, I plb, I ple);

public:
    solver(map<char, int> freq_table) : f(freq_table) {}

    map<char, string> solve(I pkb, I pke, I plb, I ple)
    {
        auto ps = d.find(make_tuple(pkb, pke, plb, ple));
        if (ps != d.cend()) return ps->second->first;

        auto r = do_solve(pkb, pke, plb, ple);
        r.insert(make_tuple(pkb, pke, plb, ple), make_pair(r, cost(r)));

        return r;
    }

private:
    map<char, string> do_solve(I pkb, I pke, I plb, I ple)
    {
        map<char, string> r;

        if (pkb == pke) return r;

        r[*pkb] = string();

        long minsofar = numeric_limits<long>::min();
        map<char, strong> nrsofar;

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

        r.insert(nbsofar.cbegin(), nrsofar.cend());
        return r;
    }

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

        vector<int> f(istream_iterator<int>(cin), istream_iterator<int>());
        map<char, int> freq_table;

        for (int i = 0; i < l; ++i)
            freq_table.insert(letters[i], f[i]);

        cout << "Keypad #" << i << ":" << endl;

        for (auto&& pair : solver(freq_table).solve(keys.cbegin(), keys.cend(), letters.cbegin(), letters.cend()))
            cout << pair->first << ": " << pair->second << endl;
    }
}
