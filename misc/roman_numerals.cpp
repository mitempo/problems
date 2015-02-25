#include <iostream>
#include <map>

using namespace std;

map<string, unsigned int> roman_values
{
    { "IV", 4 },
    { "IX", 9 },
    { "XL", 40 },
    { "XC", 90 },
    { "CD", 400 },
    { "CM", 900 },
    { "I",  1 },
    { "V",  5 },
    { "X",  10 },
    { "L",  50 },
    { "C",  100 },
    { "D",  500 },
    { "M",  1000 }
};

unsigned int roman_to_num(const char *roman)
{
    if (roman == nullptr) throw;

    unsigned long result = 0;
    unsigned long lowest_value = 1001;
    unsigned long lowest_value_count = 0;

    char buf[3];
    buf[2] = 0;

    for (const char *p = roman; *p;)
    {
        buf[0] = p[0];
        buf[1] = p[1];

        auto pv = roman_values.find(buf);
        if (buf[1] && pv != roman_values.cend())
        {
            auto value = pv->second;
            if (value >= lowest_value) throw;
            result += value;
            lowest_value = value;
            lowest_value_count = 1;
            p += 2;
        }
        else
        {
            buf[1] = 0;
            pv = roman_values.find(buf);
            if (pv == roman_values.cend()) throw;
            auto value = pv->second;
            if (value > lowest_value) throw;
            if (value == lowest_value && ++lowest_value_count > 3) throw;
            result += value;
            if (value < lowest_value)
            {
                lowest_value = value;
                lowest_value_count = 1;
            }
            ++p;
        }
    }

    return result;
}

int main()
{
    cout << roman_to_num("MDLL");
}
