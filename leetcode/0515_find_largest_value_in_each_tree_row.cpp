// https://leetcode.com/problems/find-largest-value-in-each-tree-row/description

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    struct item
    {
        TreeNode *pt;
        int d;
    };

public:
    vector<int> largestValues(TreeNode* root) {
        map<int,int> maxs;
        queue<item> q;
        q.push({root, 0});
        
        while (!q.empty())
        {
            auto e = q.front(); q.pop();
            if (e.pt == nullptr) continue;
            
            auto p = maxs.find(e.d);
            maxs[e.d] = max(p == maxs.cend() ? numeric_limits<int>::min() : p->second, e.pt->val);
            q.push({e.pt->left, e.d + 1});
            q.push({e.pt->right, e.d + 1});
        }

        vector<int> result;
        result.reserve(maxs.size());
        for (auto&& e : maxs) result.push_back(e.second);
        return result;
    }
};
