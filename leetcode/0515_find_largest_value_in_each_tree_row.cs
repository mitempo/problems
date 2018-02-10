// https://leetcode.com/problems/find-largest-value-in-each-tree-row/description/

/**
 * Definition for a binary tree node.
 * public class TreeNode {
 *     public int val;
 *     public TreeNode left;
 *     public TreeNode right;
 *     public TreeNode(int x) { val = x; }
 * }
 */
public class Solution {
    public IList<int> LargestValues(TreeNode root) {
        List<int> result = new List<int>();
        Dictionary<int, int> maxs = new Dictionary<int, int>();

        Queue<(TreeNode, int)> q = new Queue<(TreeNode, int)>();
        q.Enqueue((root, 0));
        
        while (q.Count > 0)
        {
            (TreeNode t, int d) = q.Dequeue();
            if (t == null) continue;
            
            maxs[d] = Math.Max(maxs.TryGetValue(d, out int max) ? max : t.val, t.val);
            q.Enqueue((t.left, d + 1));
            q.Enqueue((t.right, d + 1));
        }
        
        return maxs.OrderBy(pair => pair.Key).Select(pair => pair.Value).ToList();
    }
}
