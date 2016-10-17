#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <limits>

using namespace std;

template <typename T> using uset = unordered_set<T>;
template <typename K, typename V> using umap = unordered_map<K, V>;

string min_substr(const char *pstart, const uset<char>& s)
{
    int setsize = (int)s.size();
    umap<char, const char *> m;
    for (auto&& e : s) m[e] = nullptr;

    int count = 0;
    const char *pfirst = nullptr;

    const char *pminfirst = pstart;
    long long minlen = numeric_limits<long long>::max();

    for (const char *p = pstart; *p != 0; ++p)
    {
        char c = *p;

        if (s.find(c) == s.cend()) continue;

        if (m[c] == nullptr) ++count;

        if (m[c] == pfirst)
        {
            if (pfirst == nullptr)
                pfirst = p;
            else
                for (++pfirst; s.find(*pfirst) == s.cend() || m[*pfirst] != pfirst; ++pfirst)
                    ;
        }

        m[c] = p;

        if (count == setsize && p - pfirst < minlen)
        {
            pminfirst = pfirst;
            minlen = p - pfirst;                      
        }

    }

    return count < setsize ? ""s : string(pminfirst, minlen + 1);
}

template <typename T> void assrt(const T& expected, const T& actual)
{
    if (expected == actual) { cout << "PASSED" << endl; return; }

    cout << "FAIL: Expected: " << expected << ", Actual: " << actual << endl;
}

int main()
{
    assrt("cdefg"s, min_substr("abcdefghi", uset<char>{'c', 'e', 'g'} ));
    assrt("cdeefg"s, min_substr("abcdeefgaaachi", uset<char>{'c', 'e', 'g'} ));
    assrt(""s, min_substr("abcdefaaachi", uset<char>{'c', 'e', 'g'} ));
    assrt("gec"s, min_substr("abcdefgaafgechi", uset<char>{'c', 'e', 'g'} ));
}
