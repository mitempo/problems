#include <stdio.h>

int match_here(const char *re, const char *p)
{
    if (*re == 0)
        return 1;

    if (*re == '$' && re[1] == 0)
        return *p == 0;

    if (re[1] == '*')
    {
        do
        {
            if (match_here(re + 2, p))
                return 1;
        }
        while (*p != 0 && (*p++ == *re || *re == '.'));

        return 0;
    }

    return (*re == '.' && *p != 0 || *re == *p) && match_here(++re, ++p);
}

int match(const char *re, const char *p)
{
    if (*re == '^')
        return match_here(re + 1, p);

    do
    {
        if (match_here(re, p))
            return 1;
    }
    while (*p++ != 0);

    return 0;
}

int main(int argc, char *argv[])
{
    printf("%d\n", match(argv[1], argv[2]));
    return 0;
}
