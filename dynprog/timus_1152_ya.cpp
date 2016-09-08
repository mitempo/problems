#include <cstdio>
#include <vector>
#include <algorithm>
#include <map>
#include <utility>
#include <iterator>
#include <limits>
#include <numeric>

using namespace std;

map<vector<int>, int> d;

int cost(const vector<int>& v)
{
    return accumulate(v.cbegin(), v.cend(), 0);
}

vector<int> shot(const vector<int>& v, int pos)
{
    auto r(v);

    size_t n = v.size();

    r[pos++ % n] = 0;
    r[pos++ % n] = 0;
    r[pos++ % n] = 0;

    return r;
}

int lmt;

int solve(const vector<int>& v)
{
    auto pd = d.find(v);
    if (pd != d.cend()) return pd->second;

    if (cost(v) == 0) return 0;

    int cst = numeric_limits<int>::max();
    for (auto p = find_if(v.cbegin(), v.cend(), [](int e){ return e != 0; });
         p != v.cend();
         p = find_if(next(p), v.cend(), [](int e){ return e != 0; }))
    {
        vector<int> r = shot(v, p - v.cbegin());
        cst = min(cst, cost(r) + solve(r));
    }

    d.insert(decltype(d)::value_type(v, cst));
    return cst;
}

int main()
{
    int n;
    scanf("%d\n", &n);

    vector<int> v(n);
    while (n--)
        scanf("%d", &v[n]);

    printf("%d\n", solve(v));
}
