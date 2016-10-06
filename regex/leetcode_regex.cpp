#include <cstdio>
#include <string>

using namespace std;

class Solution
{
public:
    bool isMatch(string s, string p)
    {
        return is_match(s.c_str(), p.c_str());
    }
    
    bool is_match(const char *s, const char *p)
    {
        printf("%s, %s\n", s, p);

        if (*p == 0) return *s == 0;

        return p[1] == '*' && (is_match(s, p + 2) || (*s == *p || *p == '.' && *s != 0) && is_match(s + 1, p)) ||
               (*s == *p || *p == '.' && *s != 0) && is_match(s + 1, p + 1);
    }
};

int main()
{
    printf("%s\n", Solution().isMatch("acaabbaccbbacaabbbb", "a*.*b*.*a*aa*a*") ? "Match" : "NOT match");
}
