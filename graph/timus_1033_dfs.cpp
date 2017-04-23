// http://acm.timus.ru/problem.aspx?space=1&num=1033
// Labyrinth - solution via DFS.

#include <cstdio>
#include <vector>
#include <tuple>
#include <utility>
#include <string>
#include <algorithm>
#include <cstdlib>

using namespace std;

int n;
vector<string> lab;
int cnt;

void proceed(int i, int j)
{
    if (i < 0 || i == n || j < 0 || j == n)
    {
        cnt += abs(i-j) > 1;
        return;
    }
    
    if (lab[i][j] == '#')
    {
        ++cnt;
        return;
    }
    
    if (lab[i][j] == '.')
    {
        lab[i][j] = 'v';
        proceed(i-1, j);
        proceed(i+1, j);
        proceed(i, j-1);
        proceed(i, j+1);
    }
}
    
int main()
{
    scanf("%d", &n);
    
    for (int i = 0; i < n; ++i)
    {
        char buf[100];
        scanf("%s", buf);
        lab.emplace_back(buf);
    }
    
    proceed(0, 0);
    proceed(n-1, n-1);

    printf("%d", cnt * 9);
}
