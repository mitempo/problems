// https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iii

class Solution {
public:
    vector<int> get_tail_profits(const vector<int>& prices)
    {
        vector<int> tails(prices.size());

        int ma = numeric_limits<int>::min();
        int profit = 0;

        for (int i = prices.size() - 1; i >= 0; --i)
        {
            ma = max(ma, prices[i]);
            tails[i] = profit = max(profit, ma - prices[i]);
        }

        return tails;
    }

    int maxProfit(vector<int>& prices)
    {
        if (prices.size() < 2) return 0;
        
        vector<int> tail_profits = get_tail_profits(prices);

        int mi = numeric_limits<int>::max();
        int head_profit = 0;
        int profit = tail_profits[0];

        for (int i = 0; i < prices.size() - 1; ++i)
        {
            mi = min(mi, prices[i]);
            head_profit = max(head_profit, prices[i] - mi);
            profit = max(profit, head_profit + tail_profits[i+1]);
        }

        return profit;
    }
};
