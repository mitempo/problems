#include <stdio.h>

int bc[56]    = {0, 1, 1, 1};
int ac[56]    = {0, 0, 0, 0};
int cb[56]    = {0, 0, 0, 1};
int inner[56] = {0, 0, 0, 0};

class solver
{
public:
    int solve(int i)
    {
        if (bc[i] == 0) really_solve(i);
        return bc[i] + ac[i] + cb[i] + inner[i];
    }

private:
    void really_solve(int i)
    {
        if (i < 4) return;

        solve(i-1);

        cb[i] = bc[i-1];
        bc[i] = bc[i-1] + ac[i-1];
        ac[i] = cb[i-1];
        inner[i] = inner[i-1] + cb[i-1];
    }
};

int main()
{
    int n;
    scanf("%d", &n);
    printf("%d", solver().solve(n));
}
