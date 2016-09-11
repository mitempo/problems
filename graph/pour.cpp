#include <cstdio>
#include <vector>
#include <algorithm>
#include <utility>
#include <queue>

using namespace std;

struct state
{
    int a;
    int b;

    bool operator==(const state& other) const { return a == other.a && b == other.b; }
};

int ha;
int hb;
int c;

bool isfinal(const state& s)
{
    return s.a == c || s.b == c;
}

vector<state> v;
queue<pair<state, int>> q;

int solve()
{
    while (!q.empty())
    {
        const state& s = q.front().first;

        if (find(v.cbegin(), v.cend(), s) != v.cend())
        {
            q.pop();
            continue;
        }

        v.push_back(s);

        if (isfinal(s)) return q.front().second;

        if (s.a != 0) q.push(make_pair(state{0, s.b}, q.front().second + 1));
        if (s.b != 0) q.push(make_pair(state{s.a, 0}, q.front().second + 1));
        if (s.a != ha) q.push(make_pair(state{ha, s.b}, q.front().second + 1));
        if (s.b != hb) q.push(make_pair(state{s.a, hb}, q.front().second + 1));

        int m = min(s.a, hb - s.b);
        if (m != 0) q.push(make_pair(state{s.a - m, s.b + m}, q.front().second + 1));
        m = min(s.b, ha - s.a);
        if (m != 0) q.push(make_pair(state{s.a + m, hb - m}, q.front().second + 1));
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

       q.push(make_pair(state{0, 0}, 0));
       printf("%d\n", solve());
    }
}
