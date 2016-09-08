// Draft solution for http://acm.timus.ru/problem.aspx?space=1&num=1073 ("Square Country")
// TL #10

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main()
{
    int n;
    cin >> n;

    vector<long> squares;

    for (int i = 1; i*i <= n; ++i)
        squares.push_back(i*i);

    vector<long> cache;
    cache.reserve(n + 1);

    cache.push_back(0);
    cache.push_back(1);

    for (int i = 2; i <= n; ++i)
    {
        if (find(squares.cbegin(), squares.cend(), i) != squares.end())
        {
            cache.push_back(1);
            continue;
        }

        long min = numeric_limits<long>::max();

        for (int j = 1; j < i/2 + 1; ++j)
        {
            long val = cache[j] + cache[i-j];
            if (val < min) min = val;
        }

        cache.push_back(min);
    }

    cout << cache[n];
}
