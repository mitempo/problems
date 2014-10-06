// Solution for http://acm.timus.ru/problem.aspx?space=1&num=1009

#include <iostream>
#include <cassert>
#include <vector>

using namespace std;

int main()
{
    int n, k;

    cin >> n >> k;

    assert(k >= 2);
    assert(k <= 10);
    assert(n >= 2);
    assert(n + k <= 18);

    vector<int> cache;
    cache.reserve(n+1);

    cache.push_back(1);
    cache.push_back(k - 1);

    for (int i = 2; i <= n; ++i)
        cache.push_back((cache[i-1] + cache[i-2]) * (k-1));

    cout << cache[n];
}
