#include <algorithm>
#include <cstring>
#include <iostream>
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

vector<string> try_wordbreak(const char *psz, string sofar)
{
    vector<string> result;

    if (*psz == 0)
    {
        result.push_back(sofar);
    }
    else
    {
        for (size_t i = 1; i <= strlen(psz); ++i)
        {
            string candidate(psz, psz + i);
            if (!is_word(candidate)) continue;

            for (auto&& v : try_wordbreak(psz + i, sofar + " " + candidate))
                result.push_back(v);
        }
    }

    return result;
}

int main()
{
    for (auto&& s : try_wordbreak("cartoncartoncartoncarton", ""))
        cout << s << endl;
}
