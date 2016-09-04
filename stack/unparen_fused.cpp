// http://www.spoj.com/problems/CMEXPR
// Solution without trees

#include <iostream>
#include <string>
#include <utility>
#include <map>
#include <stack>

using namespace std;

int getprec(char op)
{
    const static map<char, int> precs =
    {
        {'+', 4},
        {'-', 4},
        {'*', 5},
        {'/', 5},
        {'(', 1}
    };

    auto p = precs.find(op);
    return p == precs.end() ? 10 : p->second;
}

string parenthesize_if(bool condition, const string& s)
{
    return condition ? "(" + s + ")" : s;
}

string unparen(const string& expr)
{
    stack<char> opstk;
    stack<pair<string, int>> treestk;

    auto popop = [&]()
    {
        auto n2 = move(treestk.top());
        treestk.pop();
        auto n1 = move(treestk.top());
        treestk.pop();

        treestk.push(
            make_pair(
                parenthesize_if(getprec(opstk.top()) > n1.second, n1.first) +
                    opstk.top() +
                    parenthesize_if(getprec(opstk.top()) > n2.second || getprec(opstk.top()) == n2.second && opstk.top() != '*' && opstk.top() != '+', n2.first),
                getprec(opstk.top())));

        opstk.pop();
    };

    for (const char *p = expr.c_str(); *p != 0; ++p)
    {
        char c = *p;
        if (isalpha(c))
            treestk.push(make_pair(string(1, c), 10));
        else if (c == '(')
            opstk.push(c);
        else if (c == ')')
        {
            while (opstk.top() != '(')
                popop();

            opstk.pop();
        }
        else
        {
            while (!opstk.empty() && getprec(opstk.top()) >= getprec(c))
                popop();

            opstk.push(c);
        }

    }

    while (!opstk.empty())
        popop();

    return treestk.empty() ? string() : treestk.top().first;
}

int main()
{
    int t;
    cin >> t;

    while (t--)
    {
        string expr;
        cin >> expr;
        cout << unparen(expr) << endl;
    }
}
