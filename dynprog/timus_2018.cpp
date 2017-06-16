// http://acm.timus.ru/problem.aspx?space=1&num=2018

#include <cstdio>
#include <algorithm>
#include <numeric>
#include <iterator>
#include <vector>

using namespace std;

template<typename T> inline auto sum(const vector<T>& v)
{
    T s = 0;
    for (T t : v) s += t;
    return s;
}

int main()
{
    int n, a, b;
    scanf("%d %d %d", &n, &a, &b);

    vector<long long> va(a + 1), vap(a + 1);
    vector<long long> vb(b + 1), vbp(b + 1);

    va[1] = 1;
    vb[1] = 1;

    for (int i = 2; i <= n; ++i)
    {
        vap = va;
        rotate(vap.begin(), prev(vap.end()), vap.end());
        vap[0] = 0;
        vap[1] = sum(vb) % 1000000007;

        vbp = vb;
        rotate(vbp.begin(), prev(vbp.end()), vbp.end());
        vbp[0] = 0;
        vbp[1] = sum(va) % 1000000007;

        va = std::move(vap);
        vb = std::move(vbp);
    }

    printf("%lld", (sum(va) + sum(vb)) % 1000000007); 
}
