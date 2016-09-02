// http://www.spoj.com/problems/ONP/

#include <iostream>
#include <algorithm>
#include <iterator>
#include <string>
#include <vector>
#include <utility>
#include <stack>
#include <map>

using namespace std;

const map<char, int> precs =
{
    {'^', 8},
    {'/', 7},
    {'*', 6},
    {'-', 5},
    {'+', 4},
    {'(', 1}
};

int getprec(char c)
{
    auto pprec = precs.find(c);
    return pprec != precs.cend() ? pprec->second : -1;
}

string rpn(const string& expr)
{
    string out;
    out.reserve(expr.size());

    stack<char> opstk;

    for (const char *p = expr.c_str(); *p != 0; ++p)
    {
        const char c = *p;

        if (isalpha(c))
        {
            out += c;
            continue;
        }

        if (c == '(')
        {
            opstk.push(c);
            continue;
        }

        if (c == ')')
        {
            while (!opstk.empty() && opstk.top() != '(')
            {
                out += opstk.top();
                opstk.pop(); 
            }

            if (opstk.empty()) throw exception("Unmatched parens");

            opstk.pop();
            continue;
        }

        auto cprec = getprec(c);

        while (!opstk.empty() && getprec(opstk.top()) >= cprec)
        {
            out += opstk.top();
            opstk.pop();
        }

        opstk.push(c);
    }

    while (!opstk.empty())
    {
        out += opstk.top();
        opstk.pop();
    }

    return out;
}

int main()
{
    string expr;
    cin >> expr;
    cout << rpn(expr) << endl;
}
