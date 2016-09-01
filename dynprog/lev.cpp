#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

using uint = unsigned int;

int d[501][501];

uint lev(const char *pa, uint lena, const char *pb, uint lenb)
{
    int& r = d[lena][lenb];

    if (r != -1) return (uint)r;

    if (lena == 0) { r = lenb; return (uint)r; }
    if (lenb == 0) { r = lena; return (uint)r; }

    r = min(lev(pa, lena-1, pb, lenb) + 1,
        min(lev(pa, lena,   pb, lenb - 1) + 1,
            lev(pa, lena-1, pb, lenb-1) + (pa[lena-1] != pb[lenb-1])));

    return (uint)r;
}

uint lev(string a, string b)
{
    return lev(a.c_str(), a.length(), b.c_str(), b.length());
}

int main()
{
    string a;
    string b;

    cin >> a;
    cin >> b;

    fill((int*)d, (int*)d + 501*501, -1);

    cout << lev(a, b);
}
