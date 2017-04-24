// http://acm.timus.ru/problem.aspx?space=1&num=1022
// Toposort

#include <cstdio>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

vector<vector<int>> dag(1);
vector<bool> visited;
vector<int> result;

void visit(int i)
{
    if (visited[i]) return;
    visited[i] = true;
    
    for (int d : dag[i])
        visit(d);
    
    result.push_back(i);
}

int main()
{
    int n;
    scanf("%d", &n);
    
    while (n--)
    {
        dag.emplace_back();

        for ( ; ; )
        {
            int i;
            scanf("%d", &i);
            
            if (i == 0) break;
            
            dag.back().push_back(i);
        }
    }
    
    visited.resize(dag.size());
    
    for (int i = 1; i < dag.size(); ++i)
        visit(i);

    for (auto p = result.rbegin(); p != result.rend(); ++p)
        printf("%d ", *p);
}
