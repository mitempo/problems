#include <algorithm>
#include <functional>
#include <iostream>
#include <iterator>
#include <string>
#include <utility>
#include <vector>

using namespace std;

using uint = unsigned int;

void partition_(uint n, uint min, function<void(vector<uint>)> f_visit)
{
    if (n == 0)
    {
        f_visit(vector<uint>{});
        return;
    }

    for (uint i = min; i <= n; ++i)
    {
        partition_(n - i, i, [&,i](vector<uint> v) {
            vector<uint> t{i};
            t.insert(t.end(), v.begin(), v.end());
            f_visit(t);
        });
    }
}

void partition(uint n, function<void(vector<uint>)> f_visit)
{
    partition_(n, 1, f_visit);
}

int main()
{
    uint n;
    cin >> n;

    uint partitionCount = 0;
    partition(n, [&](vector<uint> v) { ++partitionCount; for (auto&& e : v) cout << e << " "; cout << endl; });
    cout << "(" << partitionCount << ")" << endl; 
}
