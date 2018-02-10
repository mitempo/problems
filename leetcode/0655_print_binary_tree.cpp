// https://leetcode.com/problems/print-binary-tree/description/

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
    int treelc(TreeNode* pt)
    {
        return pt == nullptr ? 0 : max(treelc(pt->left), treelc(pt->right)) + 1;
    }
    
    void mfill(TreeNode *pt, vector<vector<string>>& m, int w, int i, int j)
    {
        if (pt == nullptr) return;
        
        m[i][j] = to_string(pt->val);
        mfill(pt->left, m, w / 2, i + 1, j - w / 2 - 1);
        mfill(pt->right, m, w / 2, i + 1, j + w / 2 + 1);
    }
    
    vector<vector<string>> printTree(TreeNode* root) {
        int lc = treelc(root);
        vector<vector<string>> m(lc, vector<string>((1 << lc) - 1));
        mfill(root, m, m[0].size() / 2, 0, m[0].size() / 2);
        return m;
    }
};
