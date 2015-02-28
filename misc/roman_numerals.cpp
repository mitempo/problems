#include <stdio.h>
#include <algorithm>
#include <cstring>
#include <cassert>
#include <tuple>
#include <vector>

using namespace std;

struct rdigit
{
    const char *roman;
    unsigned int value;
    unsigned int next_max_acceptable;

    friend bool operator<(unsigned int value, const rdigit& rdigit)
    {
        return value < rdigit.value;
    }
};

vector<rdigit> roman_digits
{
    { "M",  1000, 1000 },
    { "CM",  900,   90 },
    { "D",   500,  100 },
    { "CD",  400,   90 },
    { "C",   100,  100 },
    { "XC",   90,    9 },
    { "L",    50,   10 },
    { "XL",   40,    9 },
    { "X",    10,   10 },
    { "IX",    9,    0 },
    { "V",     5,    1 },
    { "IV",    4,    0 },
    { "I",     1,    1 }
};

unsigned int roman_to_num(const char *roman)
{
    if (roman == nullptr) throw;

    unsigned long result = 0;

    unsigned long last_value = 0;
    unsigned long last_value_count = 0;
    unsigned long max_acceptable = 1000;

    for (const char *p = roman; *p; )
    {
        auto pdigit = find_if(
            roman_digits.cbegin(),
            roman_digits.cend(),
            [p](const rdigit& digit)
            {
                return strncmp(digit.roman, p, strlen(digit.roman)) == 0;
            });

        if (pdigit == roman_digits.cend() ||
            pdigit->value > max_acceptable ||
            pdigit->value == last_value && ++last_value_count > 3) throw exception();

        result += pdigit->value;

        if (pdigit->value != last_value)
        {
            last_value = pdigit->value;
            last_value_count = 1;
            max_acceptable = pdigit->next_max_acceptable;
        }

        p += strlen(pdigit->roman);
    }

    return result;
}

string num_to_roman(unsigned int value)
{
    string result;

    for ( ; ; )
    {
        auto pdigit = upper_bound(roman_digits.rbegin(), roman_digits.rend(), value);

        if (pdigit-- == roman_digits.rbegin()) break;

        result += pdigit->roman;
        value -= pdigit->value;
    }

    return result;
}

int main()
{
    for (unsigned int i = 0; i <= 3999; ++i)
        assert(roman_to_num(num_to_roman(i).c_str()) == i);

    printf("Success!");
}
