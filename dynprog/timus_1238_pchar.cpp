// http://acm.timus.ru/problem.aspx?space=1&num=1238 ("Folding")

#include <algorithm>
#include <map>
#include <string>
#include <stdio.h>
#include <string.h>

using namespace std;

char sz[101];
string shortest[100][100];
string empty;

const string& solve(size_t start, size_t len)
{
    if (len == 0) return empty;

    string& min_so_far = shortest[start][len];

    if (!min_so_far.empty()) return min_so_far;

    min_so_far = string(sz + start, len);

    if (len < 3) return min_so_far;

    for (size_t pattern_len = len / 2; pattern_len > 0; --pattern_len)
    {
        for (size_t i = 0; i < min(pattern_len, len - pattern_len * 2 + 1); ++i)
        {
            size_t n_contiguous_copies = 1;

            for (size_t j = i + pattern_len; j <= len - pattern_len && strncmp(sz + start + i, sz + start + j, pattern_len) == 0; j += pattern_len)
                ++n_contiguous_copies;

            const string& pattern_solution = solve(start + i, pattern_len);

            size_t match_len = pattern_len * n_contiguous_copies;
            char match_solution[200];

            if (n_contiguous_copies == 1)
                strcpy(match_solution, pattern_solution.c_str());
            else
            {
                if (pattern_len > 1 || n_contiguous_copies > 3)
                    sprintf(match_solution, "%d(%s)", n_contiguous_copies, pattern_solution.c_str());
                else
                {
                    strncpy(match_solution, sz + start + i, match_len);
                    match_solution[match_len] = 0;
                }
            }

            char candidate[200];
            strcpy(candidate, solve(start, i).c_str());
            strcat(candidate, match_solution);
            strcat(candidate, solve(start + i + match_len, len - i - match_len).c_str());

            if (strlen(candidate) < min_so_far.size()) min_so_far = candidate;
        }
    }

    return min_so_far;
}

int main()
{
    scanf("%s", sz);
    printf("%s", solve(0, strlen(sz)).c_str());
}
