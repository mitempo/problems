// Find the closest palindrome

#include <cstdio>
#include <cstdint>
#include <string>
#include <limits>
#include <algorithm>

using namespace std;

using ulong = unsigned long;

string to_str(ulong n)
{
    char buf[40];
    snprintf(buf, sizeof(buf)/sizeof(*buf), "%lu", n);
    return buf;
}

ulong to_num(const string& s)
{
    ulong n;
    sscanf(s.c_str(), "%lu", &n);
    return n;
}

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
    return to_str(to_num(s) + 1);
}

string decrement(const string& s)
{
    return to_str(to_num(s) - 1);
}

string turn_to_palyndrome(const string& s, bool isEven)
{
    string reversed = isEven ? s : s.substr(0, s.size() - 1);
    reverse(reversed.begin(), reversed.end());
    return s + reversed;
}

string turn_to_palyndrome(const string& s, const string& mid)
{
    string reversed = s;
    reverse(reversed.begin(), reversed.end());
    return s + mid + reversed;
}

vector<string> three_closest_palindromes(const string& s)
{
    string half = first_half(s);
    string m = mid(s);
    
    return { turn_to_palyndrome(half, m), turn_to_palyndrome(increment(half), m), turn_to_palyndrome(decrement(half), m) };
}

int main()
{
    ulong n;
    scanf("%lu", &n);
    
    string s = to_str(n);

    long mindistance = numeric_limits<long>::max();
    ulong resultcandidate;
    
    for (auto&& p : three_closest_palindromes(s))
    {
        ulong nump = to_num(p);
        if (abs(nump - n) < mindistance)
        {
            mindistance = abs(nump - n);
            resultcandidate = nump;
        }
    }
    
    printf("%lu", resultcandidate);
}
