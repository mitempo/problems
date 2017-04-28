#include <cstdio>
#include <cmath>

using namespace std;

int main()
{
    const double pi = atan(1) * 4;

    double a;
    double r;
    
    scanf("%lf %lf", &a, &r);
    
    double s;
    
    if (r <= a / 2)
    {
        s = pi * r * r;
    }
    else if (r >= a / 2 * sqrt(2))
    {
        s = a * a;
    }
    else
    {
        double b = sqrt(r * r - a * a / 4);
        
        double s_triangle = b * a / 4;
        
        double alpha = pi / 4 - atan(b / a * 2);
        
        double s_sector = alpha * r * r / 2;
        
        s = (s_triangle + s_sector) * 8;
    }
    
    printf("%.3lf", s);
}
