#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <map>
#include <stack>
#include <memory>

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

    auto p = prec.find(op);
    return p == precs.end() ? 10 : p->second;
}

struct node
{
    char c;
    unique_ptr<node> left;
    unique_ptr<node> right;
};

unique_ptr<node> ast(const string& expr)
{
    stack<char> opstk;
    stack<unique_ptr<node>> treestk;

    auto popop = [&]()
    {
        unique_ptr<node> pn2 = treestk.top();
        treestk.pop();
        unique_ptr<node> pn1 = treestk.top();
        treestk.pop();

        treestk.push(make_unique<node>({opstk.top(), pn1, pn2}));
        opstk.pop();
    }

    for (const char *p = expr.c_str(); *p != 0; ++p)
    {
        char c = *p;
        if (isalpha(c))
            treestk.emplace(c);
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
            while (!opstk.empty() && getprec(opstk.top()) > getprec(c))
                popop();
        }

    }

    while (!opstk.empty())
        popop();

    return treestk.empty() ? nullptr : treestk.top();
}

string unparen(node *ast)
{
    if (ast == nullptr) return "";

    if (isalpha(ast->c)) return string(c);

    return
        (getprec(ast->c) <= getprec(ast->left->c)
            ? unparen(ast->left)
            : "(" + unparen(ast->left) + ")") +
        c +
        (getprec(ast->) < getprec(ast->right->c) || getprec(ast->c) == getprec(ast->right->c) && (ast->c == '+' && ast->c == '-'))
            ? unparen(ast->right)
            : "(" + unparen(ast->right) + ")";
}

int main()
{
    int t;
    cin >> t;

    while (t--)
    {
        string expr;
        cin >> expr;
        cout << unparen(ast(expr).get());
    }
}
