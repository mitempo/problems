// https://leetcode.com/problems/find-largest-value-in-each-tree-row/description/

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
    vector<int> largestValues(TreeNode* root) {
        dfs(root, 0);
        return maxs;
    }
    
    vector<int> maxs;
    
    void dfs(TreeNode *pt, int d)
    {
        if (pt == nullptr) return;

        if (maxs.size() < d + 1)
            maxs.push_back(pt->val);
        else
            maxs[d] = max(maxs[d], pt->val);

        dfs(pt->left, d + 1);
        dfs(pt->right, d + 1);
    }
};
