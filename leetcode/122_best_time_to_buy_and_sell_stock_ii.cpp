// https://leetcode.com/problems/best-time-to-buy-and-sell-stock-ii

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int profit = 0;
        bool has = false;
        
        for (int i = 0; i < prices.size(); ++i)
        {
            int tomorrow = i < prices.size() - 1 ? prices[i+1] : 0;
            if (prices[i] < tomorrow && !has)
            {
                has = true;
                profit -= prices[i];
            }
            else if (prices[i] > tomorrow && has)
            {
                has = false;
                profit += prices[i];
            }
        }
        
        return profit;
    }
};
