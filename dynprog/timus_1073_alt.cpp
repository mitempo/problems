// Solution for http://acm.timus.ru/problem.aspx?space=1&num=1073 ("Square Country")

#include <cstdio>
#include <vector>
#include <algorithm>
#include <limits>

using namespace std;

int main()
{
    int n;
    scanf("%d", &n);
    
    vector<int> d(n + 1);
    
    for (int i = 0; i * i < d.size(); ++i)
        d[i * i] = 1;

    for (int k = 0; k < d.size(); ++k)
    {
        if (d[k] > 0) continue;

        int minimum = numeric_limits<int>::max();

        for (int i = 1; i <= k / 2; ++i)
        {
            int candidate = d[i] + d[k-i];
            if (candidate < minimum)
                minimum = candidate;
        }

        d[k] = minimum;
    }
    
    printf("%d", d[n]);
}
