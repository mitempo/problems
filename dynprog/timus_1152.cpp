// Solution for http://acm.timus.ru/problem.aspx?space=1&num=1152 ("False mirrors")

#include <stdio.h>
#include <algorithm>
#include <climits>
#include <functional>
#include <map>
#include <vector>

using namespace std;

int main()
{
    unsigned int n;              // Number of balconies
    unsigned int balconies[20] = { 0 };

    scanf("%u", &n);
    for (size_t i = 0; i < n; ++i) scanf("%u", balconies + i);

    map<vector<bool>, unsigned int> dp_solutions;

    function<unsigned int(vector<bool>)> solve = nullptr;
    solve = [&](vector<bool> state) -> unsigned int
    {
         auto p = dp_solutions.find(state);
         if (p != dp_solutions.end()) return p->second;

         unsigned int solution = USHRT_MAX;

         for (size_t i = 0; i < state.size(); ++i)
         {
             if (!state[i]) continue;

             auto new_state = state;
             new_state[i] = false;
             new_state[(i + 1) % n] = false;
             new_state[(i + 2) % n] = false;

             unsigned int hitcount = 0;
             for (size_t i = 0; i < n; ++i)
                 if (new_state[i])
                     hitcount += balconies[i];

             solution = min(solution, solve(new_state) + hitcount);
         }

         return dp_solutions[state] = solution == USHRT_MAX ? 0 : solution;
    };

    vector<bool> start_state(n);
    fill(start_state.begin(), start_state.end(), true);
    printf("%u", solve(start_state));
}
