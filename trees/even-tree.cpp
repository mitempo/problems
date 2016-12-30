// https://www.hackerrank.com/challenges/even-tree

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <set>
#include <queue>

using namespace std;

int solve(const vector<set<int>>& g, int& r, int v)
{
    int s = 1;

    for (int i : g[v])
        s += solve(g, r, i);

    return s % 2 == 0 ? (++r, 0) : 1;
}

int main()
{
    int n, m;
    cin >> n >> m;
    
    vector<set<int>> g(n + 1);

    while (m-- > 0)
    {
        int u, v;
        cin >> u >> v;
        g[u].insert(v);
        g[v].insert(u);
    }
    
    queue<int> q;
    q.push(1);
    
    while (!q.empty())
    {
        auto v = q.front();
        q.pop();
        
        for (int i : g[v])
        {
            g[i].erase(v);
            q.push(i);
        }
    }

    int result = 0;
    
    solve(g, result, 1);
    
    cout << result - 1;    
}
