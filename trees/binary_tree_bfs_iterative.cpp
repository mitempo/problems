#include <functional>
#include <iostream>
#include <stack>
#include <type_traits>
#include <utility>

using namespace std;

template <typename Tree> void bfs(Tree t, function<void(decltype(t->value))> fVisit)
{
    stack<pair<Tree, bool>> actions;
    actions.emplace(t, false);

    while (!actions.empty())
    {
        auto action = actions.top();
        actions.pop();

        if (action.first == nullptr) continue;

        if (!action.second)
        {
            actions.emplace(action.first, true);
            actions.emplace(action.first->left, false);
        }
        else
        {
            fVisit(action.first->value);
            actions.emplace(action.first->right, false);
        }
    }
};

struct Node
{
    Node(char v, Node *l = nullptr, Node *r = nullptr) : value(v), left(l), right(r) {}

    char value;
    Node *left;
    Node *right;
};

int main()
{
    bfs(static_cast<Node*>(nullptr), [](char c){ cout << c; });
    cout << endl;
    bfs(new Node('x'), [](char c){ cout << c; });
    cout << endl;
    bfs(new Node('x', new Node('a', new Node('1'), new Node('2')), new Node('b', new Node('3'), new Node('4'))), [](char c){ cout << c; });
}
