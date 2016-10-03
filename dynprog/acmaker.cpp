// http://www.spoj.com/problems/ACMAKER

#include <cctype>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <string>
#include <cstring>
#include <type_traits>

using namespace std;

vector<string> stopwords;

template <size_t N> void readline(char (&buf)[N])
{
    fgets(buf, N, stdin);
    if (strchr(buf, '\n')) *strchr(buf, '\n') = 0;
}

int d[160][160][160];

string acronym;
string definition;

char wordIndex[160];

int s(int ia, int id, int lastWordIndex)
{
    if (ia == 0) return lastWordIndex == 0;
    if (id == 0) return 0;

    int& r = d[ia][id][lastWordIndex];

    return r != -1
        ? r
        : r = s(ia, id - 1, lastWordIndex) +
               (acronym[ia-1] == definition[id-1] && lastWordIndex - wordIndex[id-1] <= 1 ? s(ia - 1, id - 1, wordIndex[id-1]) : 0);
}

int main()
{
    for ( ; ; )
    {
        int n;
        scanf("%d\n", &n);

        if (n == 0) break;

        stopwords.clear();
        for (int i = 0; i < n; ++i)
        {
            char buf[160];
            readline(buf);
            stopwords.emplace_back(buf);
        }

        for ( ; ; )
        {
            char buf[160];
            readline(buf);

            if (string(buf) == "LAST CASE") break;

            transform(buf, buf + strlen(buf), buf, ::tolower);

            char *firstspace = strchr(buf, ' ');
            acronym = string(buf, firstspace);
            definition = string(firstspace+1);

            for (auto&& s : stopwords)
                for (size_t pos = definition.find(s); pos != string::npos; pos = definition.find(s, pos + 1))
                    if (pos != 0 && definition[pos-1] != ' ' || pos + s.size() != definition.size() && definition[pos + s.size()] != ' ')
                        continue;
                    else
                        fill_n(&definition[pos], s.size(), ' ');

            wordIndex[0] = 0;
            for (int i = 1; i < definition.size(); ++i)
                wordIndex[i] = wordIndex[i-1] + (definition[i-1] == ' ' && definition[i] != ' ');

            fill_n((int*)d, 160*160*160, -1);

            int solution = s(acronym.size(), definition.size(), wordIndex[definition.size()-1] + 1);

            transform(&acronym[0], &acronym[acronym.size()], &acronym[0], ::toupper);

            if (solution == 0)
                printf("%s is not a valid abbreviation\n", acronym.c_str());
            else
                printf("%s can be formed in %d ways\n", acronym.c_str(), solution);
        }
    }
}
