// https://leetcode.com/problems/median-of-two-sorted-arrays/

#include <vector>
#include <iostream>

using namespace std;

class Solution
{
private:
    vector<int> v1;
    vector<int> v2;

public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2)
    {
        v1 = nums1;
        v2 = nums2;

        return median(0, (int)v1.size(), 0, (int)v2.size());
    }

    double median(int i1b, int i1e, int i2b, int i2e)
    {
        if (i1b == i1e)
        {
            cout << "*";
            return median(v2, i2b, i2e);
        }

        if (i2b == i2e)
        {
            cout << "/";
            return median(v1, i1b, i1e);
        }

        if (i1e - i1b == 1 && i2e - i2b == 1)
        {
            cout << "@";
            return ((double)v1[i1b] + v2[i2b]) / 2;
        }

        double m1 = median(v1, i1b, i1e);
        double m2 = median(v2, i2b, i2e);

        return m1 < m2 ? median((i1b + i1e) / 2, i1e, i2b, (i2b + i2e - 1) / 2 + 1) :
               m1 > m2 ? median(i1b, (i1b + i1e - 1) / 2 + 1, (i2b + i2e) / 2, i2e) :
                         m1;
    }

    double median(const vector<int>& v, int ib, int ie)
    {
        int i = (ib + ie) / 2;
        return (ie - ib) % 2 != 0 ? v[i] : (v[i-1] + v[i]) / 2;
    }
};

int main()
{
    cout << Solution().findMedianSortedArrays(vector<int>{1}, vector<int>{2, 3});
}
