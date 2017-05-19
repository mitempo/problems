// https://leetcode.com/problems/distribute-candies/#/description

class Solution {
public:
    int distributeCandies(vector<int>& candies) {
        unordered_set<int> m;
        for (auto&& e : candies)
            m.insert(e);
        return min(m.size(), candies.size() / 2);
    }
};
