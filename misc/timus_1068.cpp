// Sum
// http://acm.timus.ru/problem.aspx?space=1&num=1068

#include <cstdio>

using namespace std;

int main()
{
    int n;
    scanf("%d", &n);

    long abs_n = static_cast<long>(n > 0 ? n : -n);
    long abs_sum = abs_n * (abs_n + 1) / 2;

    printf("%ld", n > 0 ? abs_sum : -abs_sum + 1);
}
