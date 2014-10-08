// Solution for http://acm.timus.ru/problem.aspx?space=1&num=1073 ("Square Country")

#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>

using namespace std;

int main()
{
    int n;
    cin >> n;

    vector<long> squares;

    for (int i = 0; i*i <= n; ++i)
        squares.push_back(i*i);

    vector<long> cache;
    cache.reserve(n + 1);

    cache.push_back(0);
    cache.push_back(1);

    for (int i = 2; i <= n; ++i)
    {
        long min = numeric_limits<long>::max();

        for (int j = 1; j < squares.size() && squares[j] <= i; ++j)
        {
            long val = squares[j] == i ? 1 : cache[squares[j]] + cache[i-squares[j]];
            if (val < min) min = val;
        }

        cache.push_back(min);
    }

    cout << cache[n];
}
