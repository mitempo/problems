#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>
#include <stdexcept>
#include <functional>

using namespace std;

template <typename T> class iter
{
public:
    iter(vector<vector<T>>& v) :
        _v(v),
        pv(v.begin()),
        p(v.empty() ? vi() : pv->begin())
    {
        skipempty();
    }

    bool is_at_end()
    {
        return pv == _v.get().end();
    }

    bool has_next()
    {
        return !is_at_end() && !iter(*this).next().is_at_end();
    }

    iter& next()
    {
        if (is_at_end()) throw runtime_error("");

        next_();
        skipempty();

        return *this;
    }

    void remove()
    {
        // if (is_at_end()) throw runtime_error("");
    }

    T& operator*()
    {
        if (is_at_end()) throw runtime_error("");
        return *p;
    }

private:
    reference_wrapper<vector<vector<T>>> _v;

    using vvi = typename vector<vector<T>>::iterator;
    using vi = typename vector<T>::iterator;

    vvi pv;
    vi p;

    void next_()
    {
        if (pv == _v.get().end()) throw runtime_error("");

        if (p != pv->end())
            ++p;
        else
        {
            ++pv;
            p = pv->begin();
        }
    }

    void skipempty()
    {
        while (pv != _v.get().end())
            if (p == pv->end())
                next_();
            else
                return;
    }
};

int main()
{
    vector<vector<int>> z = {
       { 1, 2, 3 },
       {},
       { 4, 5, 6 }
    };

    for (iter<int> p(z); !p.is_at_end(); p.next())
        cout << *p;
}
