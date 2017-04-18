// Maximum
// http://acm.timus.ru/problem.aspx?space=1&num=1079

#include <cstdio>
#include <vector>

using namespace std;

struct solver
{
    vector<long> d;
    long max = 1;
    
    solver(long n) : d(n + 1) {}
    
    long solve()
    {
        d[1] = 1;
        for (int i = 2; i < d.size(); ++i)
        {
            d[i] = i % 2 == 0 ? d[i / 2] : d[i / 2] + d[i / 2 + 1];
            if (d[i] > max) max = d[i];
        }

        return max;
    }
};

int main()
{
    for ( ; ; )
    {
        long n;
        scanf("%ld", &n);
        if (n == 0) break;
        printf("%ld\n", solver(n).solve());
    }
}