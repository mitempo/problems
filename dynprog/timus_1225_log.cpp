// http://acm.timus.ru/problem.aspx?space=1&num=1225
// O(logN) solution

#include <cstdio>

using namespace std;

template<typename T> void vm_mul(T& a1, T& a2, T b11, T b12, T b21, T b22)
{
    T r1 = b11 * a1 + b21 * a2;
    T r2 = b12 * a1 + b22 * a2;
    
    a1 = r1;
    a2 = r2;
}

template<typename T> void m_add(T& a11, T& a12, T& a21, T& a22, T b11, T b12, T b21, T b22)
{
    a11 += b11;
    a12 += b12;
    a21 += b21;
    a22 += b22;
}

template<typename T> void m_mul(T& a11, T& a12, T& a21, T& a22, T b11, T b12, T b21, T b22)
{
    T r11 = a11 * b11 + a12 * b21;
    T r12 = a11 * b12 + a12 * b22;
    T r21 = a21 * b11 + a22 * b21;
    T r22 = a21 * b12 + a22 * b22;
    
    a11 = r11;
    a12 = r12;
    a21 = r21;
    a22 = r22;
}

template<typename T> void m_pow(T& a11, T& a12, T& a21, T& a22, int n)
{
    T r11 = 1, r12 = 0, r21 = 0, r22 = 1;
    
    while (n != 0)
    {
        if (n & 1 != 0)
            m_mul(r11, r12, r21, r22, a11, a12, a21, a22);

        m_mul(a11, a12, a21, a22, a11, a12, a21, a22);
        n >>= 1;
    }
    
    a11 = r11;
    a12 = r12;
    a21 = r21;
    a22 = r22;
}

int main()
{
    int n;
    scanf("%d", &n);
    
    long long m11 = 0, m12 = 1, m21 = 1, m22 = 1;
    m_pow(m11, m12, m21, m22, n);
    
    long long a = 0;
    long long b = 2;

    vm_mul(a, b, m11, m12, m21, m22);

    printf("%lld", a);
}
