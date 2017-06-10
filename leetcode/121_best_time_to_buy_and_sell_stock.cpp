// https://leetcode.com/problems/best-time-to-buy-and-sell-stock

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        if (prices.empty()) return 0;

        int mi = prices[0];
        int gain = 0;
        
        for (int i = 1; i < prices.size(); ++i)
        {
            gain = max(gain, prices[i] - mi);
            mi = min(mi, prices[i]);
        }
        
        return gain;
    }
};
