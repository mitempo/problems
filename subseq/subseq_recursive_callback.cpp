// Problem:
//   Given a sequence, generate k-element subsequences (combinations)

#include <vector>
#include <iostream>
#include <functional>

using namespace std;

template <typename T> using v = vector<T>;

// Recursive implementation with callback
template <typename T> void subseq_(const v<T>& a, size_t n, size_t k, function<void(v<T>)> f)
{
    if (k > n) return;
    
    if (k == 0) { f(v<T>{}); return; }
	
    subseq_(a, n-1, k, f);
    subseq_(a, n-1, k-1, function<void(v<T>)>([&](v<T> ss){ ss.push_back(a[n-1]); f(ss); }));
}

template <typename T> void subseq(const v<T>& a, size_t k, function<void(v<T>)> f)
{
    return subseq_(a, a.size(), k, f);
}

int main()
{
    subseq(
        v<int>{1, 2, 3, 4, 5},
        3,
        function<void(v<int>)>([](v<int> ss)
        {
            for (auto&& e : ss) cout << e;
            cout << endl;
        }));
}
