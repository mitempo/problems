// https://leetcode.com/problems/median-of-two-sorted-arrays

// Linear solution

class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        vector<int> result;
        
        auto p1 = nums1.cbegin();
        auto p2 = nums2.cbegin();
        
        while (p1 != nums1.cend() && p2 != nums2.cend())
            result.push_back(*p1 < *p2 ? *p1++ : *p2++);
        
        while (p1 != nums1.cend())
            result.push_back(*p1++);
            
        while (p2 != nums2.cend())
            result.push_back(*p2++);
        
        if (result.empty()) return NAN;
        
        return result.size() % 2 != 0 ? result[result.size() / 2] : (result[result.size() / 2] + result[result.size() / 2 - 1]) / 2.0;
    }
};
