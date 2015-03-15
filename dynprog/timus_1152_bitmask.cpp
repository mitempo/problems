// Solution for http://acm.timus.ru/problem.aspx?space=1&num=1152 ("False mirrors")
// 10x speedup by representing the state as bitmask instead of vector<bool>.

#include <stdio.h>
#include <algorithm>

using namespace std;

unsigned short n;
unsigned short balconies[20];
unsigned short dp_solutions[0x100000];

unsigned short solve(uint32_t state)
{
     if (state == 0) return 0;

     unsigned short solution = dp_solutions[state];
     if (solution > 0) return solution;

     --solution;

     for (size_t i = 0; i < n; ++i)
     {
         if (~state & 1 << i) continue;

         uint32_t mask = 7 << i;
         mask |= mask >> n;
         mask &= (1 << n) - 1;
         uint32_t new_state = state & ~mask;

         unsigned short hitcount = 0;
         for (size_t j = 0; j < n; ++j)
             if (new_state & 1 << j)
                 hitcount += balconies[j];

         solution = min(solution, static_cast<unsigned short>(solve(new_state) + hitcount));
     }

     return dp_solutions[state] = solution;
};

int main()
{
    scanf("%hu", &n);
    for (size_t i = 0; i < n; ++i) scanf("%hu", balconies + i);

    printf("%hu", solve((1 << n) - 1));
}
