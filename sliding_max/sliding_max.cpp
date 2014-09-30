// Problem:
//   Given a sequence of N elements, find the maximum value for each window of K elements.
// Constraints:
//   O(N) in time.

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
    assert((get_sliding_max(vector<int>{}, 3) == vector<int>{}));
    assert((get_sliding_max(vector<int>{1, 2}, 3) == vector<int>{}));
    assert((get_sliding_max(vector<int>{5, 11, 8}, 3) == vector<int>{11}));
    assert((get_sliding_max(vector<int>{5, 11, 8, 14, 5, 11, 7, 35}, 3) == vector<int>{11, 14, 14, 14, 11, 35}));
}
