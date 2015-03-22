// http://acm.timus.ru/problem.aspx?space=1&num=1238 ("Folding")

#include <algorithm>
#include <map>
#include <string>
#include <stdio.h>
#include <string.h>

using namespace std;

map<string, string> shortest;

string solve(string s)
{
    auto p = shortest.find(s);
    if (p != shortest.end()) return p->second;

    if (s.size() < 3) return shortest[s] = s;

    auto min_so_far = s;

    for (size_t pattern_len = s.size() / 2; pattern_len > 0; --pattern_len)
    {
        for (size_t i = 0; i < min(pattern_len, s.size() - pattern_len * 2 + 1); ++i)
        {
            string pattern = s.substr(i, pattern_len);
            int n_contiguous_copies = 1;

            for (size_t j = i + pattern_len; j < s.size() && s.substr(j, pattern_len) == pattern; j += pattern_len)
                ++n_contiguous_copies;

            auto pattern_solution = solve(pattern);

            if (n_contiguous_copies > 1)
            {
                if (pattern_len > 1 || n_contiguous_copies > 3)
                {
                    char szEncoded[200];
                    sprintf(szEncoded, "%d(%s)", n_contiguous_copies, pattern_solution.c_str());
                    pattern_solution = szEncoded;
                }
                else
                {
                    pattern_solution = s.substr(i, n_contiguous_copies * pattern_len);
                }
            }

            auto candidate = solve(s.substr(0, i)) + pattern_solution + solve(s.substr(i + n_contiguous_copies * pattern_len));

            if (candidate.size() < min_so_far.size()) min_so_far = candidate;
        }
    }

    return shortest[s] = min_so_far;
}

int main()
{
    char input[101];
    scanf("%s", input);

    printf("%s", solve(input).c_str());
}
