// https://www.hackerrank.com/challenges/longest-increasing-subsequent

#include <vector>
#include <iostream>
#include <algorithm>
#include <utility>
#include <map>

using namespace std;

int main()
{
    long n;
    cin >> n;
    
    vector<long> v(n);
    
    for (int i = 0; i < n; ++i)
        cin >> v[i];

    map<long, long> m;
    
    for (auto&& e : v)
    {
        auto p = m.lower_bound(e);
        long len = p == m.begin() ? 1 : prev(p)->second + 1;

        while (p != m.end() && p->second <= len)
            p = m.erase(p);

        if (p == m.end() || p->first != e)
            m.insert(p, make_pair(e, len));
    }
                     
    cout << m.rbegin()->second;

    return 0;
}
