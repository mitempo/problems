// https://www.hackerrank.com/challenges/maxsubarray

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <limits>

using namespace std;

void solve(const vector<int>& v)
{
    long long s = 0;
    long long maxeh = 0;
    int maxelem = numeric_limits<int>::min(); 
    
    for (int e : v)
    {
        maxelem = max(maxelem, e);
        maxeh = max(0ll, maxeh + e);
        s = max(s, maxeh);
    }
    
    long long nonco_sum = 0;

    for (auto e : v)
        if (e > 0)
            nonco_sum += e;

    if (maxelem < 0)
        s = nonco_sum = maxelem;

    cout << s << " " << nonco_sum << endl;
}

int main()
{
    int t;
    cin >> t;
    
    while (t--)
    {
        int n;
        cin >> n;
        vector<int> v(n);
        
        for (int i = 0; i < n; ++i)
            cin >> v[i];

        solve(v);
    }
}
