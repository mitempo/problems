/**
 * Definition for singly-linked list.
 * public class ListNode {
 *     public int val;
 *     public ListNode next;
 *     public ListNode(int x) { val = x; }
 * }
 */
public class Solution {
    public ListNode AddTwoNumbers(ListNode l1, ListNode l2) {
        ListNode result = new ListNode(-1); // dummy
        ListNode last = result;

        int carry = 0;
        
        while (l1 != null || l2 != null)
        {
            int s = (l1 == null ? 0 : l1.val) + (l2 == null ? 0 : l2.val) + carry;
            int d = s % 10;
            carry = s > 9 ? 1 : 0;
            last.next = new ListNode(d);
            last = last.next;
            
            l1 = l1 == null ? null : l1.next;
            l2 = l2 == null ? null : l2.next;
        }

        if (carry > 0) last.next = new ListNode(1);
        return result.next;
    }
}
