#include <algorithm>
#include <cassert>
#include <cstdint>
#include <iterator>
#include <iostream>
#include <vector>

template <typename T> struct double_size_type;

template <> struct double_size_type<uint8_t>  { using type = uint16_t; };
template <> struct double_size_type<uint16_t> { using type = uint32_t; };
template <> struct double_size_type<uint32_t> { using type = uint64_t; };

template <typename T> struct weight
{
    constexpr static auto value = static_cast<typename double_size_type<T>::type>(std::numeric_limits<T>::max() + 1);
};

template <typename Carrier = uint8_t> class bigint
{
public:
    using carrier_t = Carrier;

    constexpr static auto radix = weight<carrier_t>::value;
    constexpr static auto all_ones = static_cast<carrier_t>(-1);

private:
    bool neg = false;
    std::vector<carrier_t> digits;

    friend void test();

public:
    bigint() = default;

    auto operator~() const
    {
        auto r = *this;
        r.neg = !r.neg;

        for (auto& d : r.digits)
            d = ~d;

        return r;
    }

    auto operator-() const
    {
        return ++(~(*this));
    }

    std::string to_string() const
    {
        if (neg)
        {
            return "-" + (-(*this)).to_string();
        }
        
        std::vector<int> decs = { 0 };
        
        for (auto p = digits.crbegin(); p != digits.crend(); ++p)
        {
            int carryover = 0;
            for (auto pdec = decs.begin(); pdec != decs.end(); ++pdec)
            {
                carryover += *pdec * radix + *p;
                *pdec = carryover % 10;
                carryover /= 10;
            }

            while (carryover != 0)
            {
                decs.push_back(carryover % 10);
                carryover /= 10;
            }
        }

        std::string s;
        std::transform(decs.crbegin(), decs.crend(), std::back_inserter(s), [](int i){ return '0' + i; });

        return s;
    }

    decltype(auto) operator++()
    {
        bool cont = true;
        auto p = digits.begin();

        while (cont && p != digits.end())
            cont = ++(*p++) == 0;
        
        if (cont)
        {
            if (neg)
            {
                digits.clear();
                neg = false;
            }
            else
                digits.push_back(1);
        }
        else
        {
            if (neg && p == digits.end() && digits.back() == all_ones)
                digits.pop_back();
        }

        return *this;
    }

    auto operator++(int)
    {
        auto temp = *this;
        (*this)++;
        return temp;
    }

    decltype(auto) operator--()
    {
        bool cont = true;
        auto p = digits.begin();

        while (cont && p != digits.end())
            cont = --(*p++) == all_ones;
        
        if (cont)
        {
            if (neg)
            {
                digits.push_back(-2);
            }
            else
            {
                digits.clear();
                neg = true;
            }
        }
        else
        {
            if (!neg && p == digits.end() && digits.back() == 0)
                digits.pop_back();
        }

        return *this;
    }

    auto operator--(int)
    {
        auto temp = *this;
        (*this)--;
        return temp;
    }
};

void test()
{
    bigint<> z;
    assert(!z.neg);
    assert(z.digits.empty());
    assert(z.to_string() == "0");
    
    --z;
    assert(z.neg);
    assert(z.digits.empty());
    assert(z.to_string() == "-1");
    
    ++z;
    assert(!z.neg);
    assert(z.digits.empty());
    assert(z.to_string() == "0");
    
    --z;
    assert(z.neg);
    assert(z.digits.empty());
    assert(z.to_string() == "-1");

    --z;
    assert(z.neg);
    assert(z.digits == std::vector<uint8_t>{254});
    assert(z.to_string() == "-2");

    for (int i = 0; i < 125; ++i)
        --z;

    assert(z.neg);
    assert(z.digits == std::vector<uint8_t>{129});
    assert(z.to_string() == "-127");

    --z;
    assert(z.neg);
    assert(z.digits == std::vector<uint8_t>{static_cast<uint8_t>(128)});
    assert(z.to_string() == "-128");

    --z;
    assert(z.neg);
    assert(z.digits == std::vector<uint8_t>{127});
    assert(z.to_string() == "-129");

    for (int i = 0; i < 127; ++i)
        --z;

    assert(z.neg);
    assert(z.digits == std::vector<uint8_t>{0});
    assert(z.to_string() == "-256");

    --z;
    assert(z.neg);
    assert((z.digits == std::vector<uint8_t>{255, 254}));
    assert(z.to_string() == "-257");

    ++z;
    assert(z.neg);
    assert((z.digits == std::vector<uint8_t>{0}));
    assert(z.to_string() == "-256");

    for (int i = 0; i < 511; ++i)
        ++z;

    assert(!z.neg);
    assert((z.digits == std::vector<uint8_t>{255}));
    assert(z.to_string() == "255");

    ++z;
    assert(!z.neg);
    assert((z.digits == std::vector<uint8_t>{0, 1}));
    assert(z.to_string() == "256");

    --z;
    assert(!z.neg);
    assert((z.digits == std::vector<uint8_t>{255}));
    assert(z.to_string() == "255");
}

int main()
{
    test();
}
