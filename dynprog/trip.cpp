#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <unordered_set>

using namespace std;

using uint = unsigned int;
template <typename T> using uset = unordered_set<T>;

struct cell
{
    int len;
    uset<string> cands;
};

class solver
{
    cell d[81][81];

    cell& s(const char *pa, uint lena, const char *pb, uint lenb)
    {
        cell& r = d[lena][lenb];

        if (!r.cands.empty()) return r;

        if (lena == 0 || lenb == 0)
        {
            uset<string> v{""};
            r = {0, v};
            return r;
        }

        if (pa[lena-1] == pb[lenb-1])
        {
            const cell& rr = s(pa, lena-1, pb, lenb-1);
            uset<string> v;
            transform(rr.cands.cbegin(), rr.cands.cend(), inserter(v, v.end()), [=](string str){ return str.append(1, pa[lena-1]); });
            r = {rr.len + 1, v};
            return r;
        }

        const cell& ra = s(pa, lena-1, pb, lenb);
        const cell& rb = s(pa, lena, pb, lenb-1);

        if (ra.len > rb.len)
        {
            r = ra;
            return r;
        }

        if (rb.len > ra.len)
        {
            r = rb;
            return r;
        }

        auto v(ra.cands);
        v.insert(rb.cands.cbegin(), rb.cands.cend());

        r = {ra.len, v};
        return r;
    }

public:
    uset<string> s(string a, string b)
    {
        return s(a.c_str(), a.length(), b.c_str(), b.length()).cands;
    }
};

int main()
{
    int t;
    cin >> t;

    for (int i = 0; i < t; ++i)
    {
        string a;
        string b;

        cin >> a >> b;

        for (auto&& e : solver().s(a, b)) cout << e << endl;
        cout << endl;
    }
}
