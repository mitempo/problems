#include <functional>
#include <iostream>
#include <stack>

using namespace std;

// Iterative inorder DFS traversal of a binary tree.
// BinaryTree must be a (possibly smart) pointer to a struct with 'value', 'left', and 'right'
// members. 
template <typename BinaryTree> void dfs_in(BinaryTree t, function<void(decltype(t->value))> fVisit)
{
    stack<BinaryTree> todo;

    for ( ; ; )
    {
        while (t != nullptr)
        {
            todo.push(t);
            t = t->left;
        }

        if (todo.empty()) break;

        fVisit(todo.top()->value);
        t = todo.top()->right;
        todo.pop();
    }
}

// Iterative preorder DFS traversal of a binary tree.
// BinaryTree must be a (possibly smart) pointer to a struct with 'value', 'left', and 'right'
// members. 
template <typename BinaryTree> void dfs_pre(BinaryTree t, function<void(decltype(t->value))> fVisit)
{
    stack<BinaryTree> todo;

    for ( ; ; )
    {
        while (t != nullptr)
        {
            fVisit(t->value);
            todo.push(t->right);
            t = t->left;
        }

        if (todo.empty()) break;

        t = todo.top();
        todo.pop();
    }
}

struct Node
{
    Node(char v, Node *l = nullptr, Node *r = nullptr) : value(v), left(l), right(r) {}

    char value;
    Node *left;
    Node *right;
};

int main()
{
    dfs_in(static_cast<Node*>(nullptr), [](char c){ cout << c; });
    cout << endl;

    dfs_in(new Node('x'), [](char c){ cout << c; });
    cout << endl;

    dfs_in(new Node('*', new Node('+', new Node('1'), new Node('2')), new Node('-', new Node('3'), new Node('4'))), [](char c){ cout << c; });
    cout << endl;

    dfs_pre(static_cast<Node*>(nullptr), [](char c){ cout << c; });
    cout << endl;

    dfs_pre(new Node('x'), [](char c){ cout << c; });
    cout << endl;

    dfs_pre(new Node('*', new Node('+', new Node('1'), new Node('2')), new Node('-', new Node('3'), new Node('4'))), [](char c){ cout << c; });
    cout << endl;
}
