#include <stdio.h>
#include <algorithm>
#include <cstring>
#include <cassert>
#include <functional>
#include <vector>

using namespace std;

struct rdigit
{
    const char *roman;
    unsigned short value;

    friend bool operator<(unsigned short value, const rdigit& rdigit)
    {
        return value < rdigit.value;
    }
};

vector<rdigit> roman_digits
{
    { "M",  1000 },
    { "CM",  900 },
    { "D",   500 },
    { "CD",  400 },
    { "C",   100 },
    { "XC",   90 },
    { "L",    50 },
    { "XL",   40 },
    { "X",    10 },
    { "IX",    9 },
    { "V",     5 },
    { "IV",    4 },
    { "I",     1 }
};

short roman_to_num(const char *roman)
{
    short result = 0;

    unsigned short last_value = 1000;
    unsigned short last_value_count = 0;
    unsigned short max_acceptable = 1000;

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
            pdigit->value == last_value && ++last_value_count > 3) return -1;

        result += pdigit->value;

        if (pdigit->value != last_value)
        {
            last_value = pdigit->value;
            last_value_count = 1;
            max_acceptable = (pdigit-1)->value - pdigit->value - 1;
        }

        p += strlen(pdigit->roman);
    }

    return result;
}

string num_to_roman(unsigned short value)
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

// Generates all roman "digits" sequences with the total length of distance(pb, pe)
template <typename I> void gen(I pb, I pe, function<void()> f)
{
    if (pb == pe)
    {
        f();
        return;
    }

    for (auto&& e : roman_digits)
    {
        if (strlen(e.roman) > static_cast<size_t>(distance(pb, pe))) continue;

        copy(e.roman, e.roman+strlen(e.roman), pb);
        gen(pb + strlen(e.roman), pe, f);
    }
}

int main()
{
    for (unsigned short i = 0; i <= 3999; ++i)
        assert(roman_to_num(num_to_roman(i).c_str()) == i);

    char buf[8] = {};

    for (size_t i = 0; i < sizeof buf/sizeof *buf; ++i)
        gen(buf, buf + i, [&buf]()
                          {
                              short n = roman_to_num(buf);
                              if (n >= 0) assert(num_to_roman(n) == buf);
                          });

    printf("Success!");
}
