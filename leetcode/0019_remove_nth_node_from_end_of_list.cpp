// https://leetcode.com/problems/remove-nth-node-from-end-of-list/description/

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode **p1 = &head;
        ListNode **p2 = p1;
        while (n--) p2 = &(*p2)->next;
        while (*p2 != nullptr) p1 = &(*p1)->next, p2 = &(*p2)->next;
        *p1 = (*p1)->next;
        return head;
    }
};
