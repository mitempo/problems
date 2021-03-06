#include <cstdio>
#include <vector>
#include <algorithm>
#include <utility>
#include <queue>
#include <set>

using namespace std;

struct state
{
    int a;
    int b;

    bool operator==(const state& other) const { return a == other.a && b == other.b; }
    bool operator<(const state& other) const { return a < other.a || a == other.a && b < other.b; }
};

int ha;
int hb;
int c;

bool isfinal(const state& s)
{
    return s.a == c || s.b == c;
}

set<state> v;
queue<pair<state, int>> q;

void conditionally_push(state&& s, int d)
{
    if (v.find(s) == v.cend())
        q.push({s, d});
}

int solve()
{
    while (!q.empty())
    {
        state s = q.front().first;
        int d = q.front().second;

        q.pop();
        v.insert(s);

        if (isfinal(s)) return d;

        if (s.a != 0) conditionally_push({0, s.b}, d + 1);
        if (s.b != 0) conditionally_push({s.a, 0}, d + 1);
        if (s.a != ha) conditionally_push({ha, s.b}, d + 1);
        if (s.b != hb) conditionally_push({s.a, hb}, d + 1);

        int m = min(s.a, hb - s.b);
        if (m != 0) conditionally_push({s.a - m, s.b + m}, d + 1);
        m = min(s.b, ha - s.a);
        if (m != 0) conditionally_push({s.a + m, s.b - m}, d + 1);
    }

    return -1;
}

int main()
{
    int t;
    scanf("%d\n", &t);

    while (t--)
    {
       scanf("%d\n%d\n%d\n", &ha, &hb, &c);

       v.clear();
       q = decltype(q){};
       q.push(make_pair(state{0, 0}, 0));
       printf("%d\n", solve());
    }
}
