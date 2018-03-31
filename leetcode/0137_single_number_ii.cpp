// https://leetcode.com/problems/single-number-ii/description/

class Solution {
public:
    int singleNumber(vector<int>& nums) {
        using t = remove_reference_t<decltype(nums)>::value_type;
        size_t bitcount = sizeof(t) * 8;
        vector<long long> counts(bitcount, 0);

        for (auto e : nums)
            for (int i = 0; i < bitcount; ++i)
                counts[i] = (counts[i] + ((e & 1 << i) != 0)) % 3;

        t result = 0;
        for (int i = 0; i < bitcount; ++i)
            result |= (counts[i] > 0) << i;
        
        return result;
    }
};
