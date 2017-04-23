// http://acm.timus.ru/problem.aspx?space=1&num=1033
// Labyrinth - solution via BFS

#include <cstdio>
#include <queue>
#include <algorithm>
#include <vector>
#include <string>
#include <utility>
#include <tuple>

using namespace std;

template <typename T> using v = vector<T>;

int main()
{
    int n;
    scanf("%d", &n);
    
    v<string> lab;
    
    for (int i = 0; i < n; ++i)
    {
        char buf[50];
        scanf("%s", buf);
        lab.emplace_back(buf);
    }

    queue<pair<int,int>> q;
    q.emplace(0, 0); 
    q.emplace(n-1, n-1); 
    lab[0][0] = 'v';
    lab[n-1][n-1] = 'v';

    int count = 0;
    
    auto neighbor = [&](int i, int j) -> void
    {
        if (i == -1)
        {
            count += j != 0;
            return;
        }
        
        if (j == -1)
        {
            count += i != 0;
            return;
        }
        
        if (i == n)
        {
            count += j != n-1;
            return;
        }
        
        if (j == n)
        {
            count += i != n-1;
            return;
        }
        
        if (lab[i][j] == '#')
        {
            ++count;
            return;
        }
        
        if (lab[i][j] == '.')
        {
            q.emplace(i, j);
            lab[i][j] = 'v';
            return;
        }
    };
    
    while (!q.empty())
    {
        int i, j;
        tie(i, j) = q.front();
        q.pop();

        neighbor(i-1, j);
        neighbor(i+1, j);
        neighbor(i, j-1);
        neighbor(i, j+1);
    }

    printf("%d", count * 9);
}
