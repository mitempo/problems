#include <iostream>
#include <vector>
#include <limits>
#include <utility>
#include <cassert>

using namespace std;

int main()
{
    int l1, l2, l3;
    int c1, c2, c3;
    int n; // Number of stations
    int start, end;

    cin >> l1 >> l2 >> l3 >> c1 >> c2 >> c3;
    cin >> n;
    cin >> start >> end;

    assert(1 <= l1);
    assert(l1 <= l2);
    assert(l2 <= l3);

    assert(1 <= c1);
    assert(c1 <= c2);
    assert(c2 <= c3);

    assert(n > 0);

    assert(start > 0);
    assert(start <= n);
    assert(end > 0);
    assert(end <= n);

    vector<int> dist(n-1);

    for (int i = 1; i < n; ++i)
        cin >> dist[i];

    if (start > end) swap(start, end);

    vector<int> min_prices(n, numeric_limits<int>::max());
    min_prices[start-1] = 0;

    for (int i = start; i <= end-1; ++i)
    {
        for (int j = i-1; j >= start-1; --j)
        {
            int d = dist[i] - dist[j];

            int price = d <= l1 ? c1 :
                        d <= l2 ? c2 :
                        d <= l3 ? c3 :
                                  numeric_limits<int>::max();

            if (price == numeric_limits<int>::max()) break;

            price += min_prices[j];

            if (price < min_prices[i]) min_prices[i] = price;
        }
    }

    cout << min_prices[end-1];
}
