// Big number arithmetic: addition and subtraction of unsigned integers.

#include <cstdint>
#include <vector>
#include <algorithm>
#include <iostream>
#include <stdexcept>

using namespace std;

// A type that is twice the carrier type's size is required for multiplication
// of the items of the big_uint's internal vector.
// On top of that, using the wider type makes overflow and underflow detection more convenient
// for addition and subtraction.

template <typename T> struct double_size_type;
template <> struct double_size_type<uint8_t>  { using type = uint16_t; };
template <> struct double_size_type<uint16_t> { using type = uint32_t; };
template <> struct double_size_type<uint32_t> { using type = uint64_t; };

// TODO: For practical use the default TCarrier should be uint32_t. uint8_t is convenient
// for testing: you don't have to use very large numbers.
// TODO: For practical use there should be eight overloads for all the arithmetic
// operators, covering all overloadable pairs of {big_uint&&, const big_uint&, uint}.
template <typename TCarrier = uint8_t> class big_uint
{
public:
    using carrier_t = TCarrier;
    using dcarrier_t = typename double_size_type<carrier_t>::type;

private:
    vector<carrier_t> data;

    static carrier_t add_with_carryover(carrier_t augend, carrier_t addend, bool& carryover)
    {
        dcarrier_t wide_augend = static_cast<dcarrier_t>(augend);
        dcarrier_t wide_addend = static_cast<dcarrier_t>(addend);
        dcarrier_t wide_sum = wide_augend + wide_addend + carryover;

        carryover = wide_sum > numeric_limits<carrier_t>::max();
        return static_cast<carrier_t>(wide_sum);
    }

    static carrier_t subtract_with_carryover(carrier_t minuend, carrier_t subtrahend, bool& carryover)
    {
        dcarrier_t wide_minuend = static_cast<dcarrier_t>(minuend);
        dcarrier_t wide_subtrahend = static_cast<dcarrier_t>(subtrahend);
        dcarrier_t wide_difference = wide_minuend - wide_subtrahend - carryover;

        carryover = wide_difference > wide_minuend;
        return static_cast<carrier_t>(wide_difference);
    }

    static carrier_t multiply_with_carryover(carrier_t multiplicand, carrier_t multiplier, carrier_t& carryover)
    {
        dcarrier_t wide_multiplicand = static_cast<dcarrier_t>(multiplicand);
        dcarrier_t wide_product = wide_multiplicand * multiplier + carryover;

        carryover = static_cast<carrier_t>(wide_product / (static_cast<dcarrier_t>(numeric_limits<carrier_t>::max()) + 1));
        return static_cast<carrier_t>(wide_product);
    }

    big_uint(vector<carrier_t> raw_data)
    {
        data = raw_data;
    }

public:
    big_uint(unsigned int value = 0)
    {
        while (value > 0)
        {
            data.push_back(value % (static_cast<dcarrier_t>(numeric_limits<carrier_t>::max()) + 1));
            value /= static_cast<dcarrier_t>(numeric_limits<carrier_t>::max()) + 1;
        }
    }

    friend big_uint operator+(const big_uint& a, const big_uint& b)
    {
        auto shorter_size = min(a.data.size(), b.data.size());
        auto longer_size = a.data.size() == shorter_size ? b.data.size() : a.data.size();
        const auto& shorter = a.data.size() == shorter_size ? a.data : b.data;
        const auto& longer = &shorter == &a.data ? b.data : a.data;

        vector<carrier_t> result;
        result.reserve(longer_size);

        bool carryover = false;
        for (int i = 0; i < longer_size; ++i)
            result.push_back(add_with_carryover(longer[i], i < shorter_size ? shorter[i] : 0, carryover));

        if (carryover) result.push_back(1);
        return result;
    }

    friend big_uint operator-(const big_uint& a, const big_uint& b)
    {
        if (a.data.size() < a.data.size()) throw underflow_error("big_uint");

        vector<carrier_t> result;
        result.reserve(a.data.size());

        bool carryover = false;
        for (int i = 0; i < a.data.size(); ++i)
            result.push_back(subtract_with_carryover(a.data[i], i < b.data.size() ? b.data[i] : 0, carryover));

        if (carryover) throw underflow_error("big_uint");

        auto new_size = result.size();
        for (auto i = result.size() - 1; i < numeric_limits<typename decltype(result)::size_type>::max(); --i)
            if (result[i] == 0) new_size = i;

        result.resize(new_size);
        return result;
    }

    friend big_uint operator*(const big_uint& a, carrier_t b)
    {
        vector<carrier_t> result;

        if (a.data.empty() || b == 0) return result;

        result.reserve(a.data.size() + 1);

        carrier_t carryover = 0;
        for (int i = 0; i < a.data.size(); ++i)
            result.push_back(multiply_with_carryover(a.data[i], b, carryover));

        if (carryover) result.push_back(carryover);
        return result;
    }

    string to_string()
    {
        using decdigit_t = int;   // Integral type to represent a decimal digit

        vector<decdigit_t> decimal_digits{ 0 }; // Each element is the value of a decimal digit

        for (auto p = data.rbegin(); p != data.rend(); ++p)
        {
            carrier_t carryover = *p;
            for (auto& digit : decimal_digits)
            {
                dcarrier_t value = static_cast<dcarrier_t>(digit * (numeric_limits<carrier_t>::max()+1) + carryover);
                digit = static_cast<decdigit_t>(value % 10);
                carryover = static_cast<carrier_t>(value / 10);
            }

            while (carryover > 0)
            {
                decimal_digits.push_back(carryover % 10);
                carryover /= 10;
            }
        }

        string s;
        s.reserve(decimal_digits.size());

        for (auto p = decimal_digits.rbegin(); p != decimal_digits.rend(); ++p)
            s.push_back(static_cast<char>(*p + '0'));

        return s;
    }
};

int main()
{
    auto c = big_uint<>(0) - big_uint<>(0) + big_uint<>(2000) + big_uint<>(1000) - big_uint<>(500) + big_uint<>(0) - big_uint<>(0) + big_uint<>(1);
    cout << (c * 100).to_string().c_str();
}
