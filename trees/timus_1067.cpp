// http://acm.timus.ru/problem.aspx?space=1&num=1067
// Disk Tree

#include <cstdio>
#include <string>
#include <map>

using namespace std;

struct node
{
    map<string, node> children;
};

class splitter
{
public:
    splitter(const string& source, char separator) : s(source), sep(separator), p(s.c_str()) {}

    string cur;

    bool move_next()
    {
        if (*p == 0) return false;
        
        const char *pend = p;
        while (*pend != sep && *pend != 0)
            ++pend;
        
        cur = string(p, pend-p);
        p = *pend == 0 ? pend : pend + 1;
        return true;
    }

private:
    string s;
    char sep;
    const char *p;
};

void preorder_print(const node& node, int indent = 0)
{
    for (auto&& pair : node.children)
    {
        printf("%s%s\n", string(indent, ' ').c_str(), pair.first.c_str());
        preorder_print(pair.second, indent + 1);
    }
}

int main()
{
    int n;
    scanf("%d", &n);
    
    node root;
    
    while (n--)
    {
        char buf[100];
        scanf("%s", buf);
        
        node *pnode = &root;
        
        splitter splitter(buf, '\\');
        
        while (splitter.move_next())
            pnode = &pnode->children[splitter.cur];
    }
    
    preorder_print(root);
}
