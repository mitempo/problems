#include <algorithm>
#include <cstring>
#include <iostream>
#include <iterator>
#include <map>
#include <string>
#include <vector>

using namespace std;

vector<string> words
{
    "this", "is", "a", "am", "i", "that", "cat", "car", "ton", "carton"
};

bool is_word(const string& s)
{
    return find(words.cbegin(), words.cend(), s) != words.cend();
}

vector<vector<string>> try_wordbreak(const char *psz)
{
    vector<vector<string>> result;

    if (*psz == 0)
    {
        result.push_back(vector<string>{});
    }
    else
    {
        for (size_t i = 1; i <= strlen(psz); ++i)
        {
            string candidate(psz, psz + i);
            if (!is_word(candidate)) continue;

            for (auto&& v : try_wordbreak(psz + i))
            {
                vector<string> z{candidate};
                copy(v.cbegin(), v.cend(), back_inserter(z));
                result.push_back(z);
            }
        }
    }

    return result;
}

int main()
{
    for (auto&& v : try_wordbreak("cartoncartoncartoncarton"))
    {
        for (auto&& s : v)
            cout << s << " ";

        cout << endl;
    }
}
