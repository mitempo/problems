// https://leetcode.com/problems/partition-list/description/

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
    ListNode* partition(ListNode* head, int x) {
        ListNode *gt = nullptr;
        ListNode **pip = &gt;
        
        ListNode **pp = &head;
        while (*pp != nullptr)
        {
            if ((*pp)->val >= x)
            {
                *pip = *pp;
                *pp = (*pp)->next;

                pip = &(*pip)->next;
                *pip = nullptr;
            }
            else
                pp = &(*pp)->next;
        }
        
        *pp = gt;
        return head;
    }
};
