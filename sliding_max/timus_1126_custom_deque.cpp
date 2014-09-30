// http://acm.timus.ru/problem.aspx?space=1&num=1126

// Input
// The first line contains a number M, 2 <= M <= 14000. Then values (N integers) measured by the device follow each one in its line.
// There is a number -1 in the end. M <= N <= 25000.
// Output
// a sequence of readouts, each one in its line.

#include <iostream>
#include <vector>
#include <utility>
#include <cassert>

using namespace std;
using uint = unsigned int;

// Custom deque with limited functionality:
// 1. Statically-defined capacity;
// 2. No support for push_front().
template <typename T, uint Capacity> class static_semi_deque
{
public:
    static_semi_deque() : iBegin(0)
    {
        buffer.reserve(Capacity);
    }

    bool empty() { return iBegin == buffer.size(); }

    void push_back(const T& value) { buffer.push_back(value); }
    void push_back(T&& value) { buffer.push_back(value); }

    void pop_back() { buffer.pop_back(); }

    void pop_front() { T temp = move(buffer[iBegin++]); }

    const T& front() { return buffer[iBegin]; } 
    const T& back() { return buffer.back(); } 

private:
    vector<T> buffer;
    uint iBegin;
};

template <typename T> vector<T> get_sliding_max(const vector<T>& input, uint k)
{
    static_semi_deque<pair<uint,T>, 30000> deq;
    vector<T> result;
    
    for (uint i = 0; i < input.size(); ++i)
    {
        if (!deq.empty() && deq.front().first + k <= i) deq.pop_front();
        while (!deq.empty() && deq.back().second < input[i]) deq.pop_back();
        deq.push_back({i, input[i]});
        if (i >= k - 1) result.push_back(deq.front().second);
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
