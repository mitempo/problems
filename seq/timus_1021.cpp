// http://acm.timus.ru/problem.aspx?space=1&num=1021

#include <cstdio>
#include <vector>
#include <iterator>

using namespace std;

vector<int> read_vector_from_stdin()
{
    int n;
    vector<int> v;
    
    scanf("%d", &n);
    v.reserve(n);
    
    while (n--)
    {
        int a;
        scanf("%d", &a);
        v.push_back(a);
    }
    
    return v;
}

const int TARGET = 10000;

int main()
{
    vector<int> v1 = read_vector_from_stdin();
    vector<int> v2 = read_vector_from_stdin();

    auto p1 = v1.cbegin();
    auto p2 = v2.cbegin();
    
    int s;

    while (p1 != v1.cend())
    {
        while (p2 != v2.cend() && (s = *p1 + *p2) > TARGET)
            ++p2;
        
        if (p2 == v2.cend()) break;

        if (s == TARGET)
        {
            printf("YES");
            return 0;
        }
        
        ++p1;
    }
    
    printf("NO");
}
