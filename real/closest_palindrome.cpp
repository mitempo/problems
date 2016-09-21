// Find the closest palindrome

#include <cstdio>
#include <cstdint>
#include <string>
#include <limits>
#include <algorithm>
#include <vector>

using namespace std;

using ulong = unsigned long;

string first_half(const string& s)
{
    return s.substr(0, s.size() / 2);
}

string mid(const string& s)
{
    return s.size() % 2 == 0 ? string("") : s.substr(s.size() / 2, 1); 
}

string increment(const string& s)
{
    return to_string(stoul(s) + 1);
}

string decrement(const string& s)
{
    return to_string(stoul(s) - 1);
}

string mirror(const string& s, const string& mid)
{
    string reversed = s;
    reverse(reversed.begin(), reversed.end());
    return s + mid + reversed;
}

vector<string> three_closest_palindromes(const string& s)
{
    string half = first_half(s);
    string m = mid(s);
    
    return
    {
        mirror(half, m),
        mirror(increment(half), m),
        mirror(decrement(half), m)
    };
}

int main()
{
    ulong n;
    scanf("%lu", &n);
    
    string s = to_string(n);

    ulong mindistance = numeric_limits<ulong>::max();
    ulong resultcandidate;
    
    for (auto&& p : three_closest_palindromes(s))
    {
        ulong nump = stoul(p);
        ulong distance = max(nump, n) - min(nump, n);
        if (distance < mindistance)
        {
            mindistance = distance;
            resultcandidate = nump;
        }
    }
    
    printf("%lu", resultcandidate);
}
