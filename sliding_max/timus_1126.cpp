// http://acm.timus.ru/problem.aspx?space=1&num=1126

// Input
// The first line contains a number M, 2 <= M <= 14000. Then values (N integers) measured by the device follow each one in its line.
// There is a number -1 in the end. M <= N <= 25000.
// Output
// a sequence of readouts, each one in its line.

#include <iostream>
#include <deque>
#include <vector>
#include <utility>
#include <cassert>

using namespace std;
using uint = unsigned int;

template <typename T> vector<T> get_sliding_max(const vector<T>& input, uint k)
{
    deque<pair<uint,T>> deq;
    vector<T> result;
    
    for (uint i = 0; i < input.size(); ++i)
    {
        if (!deq.empty() && deq.back().first + k <= i) deq.pop_back();
        while (!deq.empty() && deq.front().second < input[i]) deq.pop_front();
        deq.push_front({i, input[i]});
        if (i >= k - 1) result.push_back(deq.back().second);
    }
    
    return result;
}

int main()
{
    int m;         // Sliding window size
    vector<int> v; // Element sequence

    cin >> m;

    for ( ; ; )
    {
        int e;
        cin >> e;
        if (e == -1) break;
        v.push_back(e);
    }

    auto solution = get_sliding_max(v, m);
    for (auto e : solution) cout << e << endl;
}
