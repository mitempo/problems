// https://leetcode.com/problems/remove-duplicates-from-sorted-list-ii/description/

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
    ListNode* deleteDuplicates(ListNode* head) {
        ListNode **pp = &head;
        
        while (*pp != nullptr && (*pp)->next != nullptr)
        {
            if ((*pp)->val != (*pp)->next->val)
            {
                pp = &(*pp)->next;
                continue;
            }
            
            for (int v = (*pp)->val; *pp != nullptr && (*pp)->val == v; *pp = (*pp)->next)
                ;
        }
        
        return head;
    }
};
