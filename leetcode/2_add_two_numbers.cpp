// https://leetcode.com/problems/add-two-numbers

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
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode *head = nullptr;
        ListNode **insertion_point = &head;
        
        int carry = 0;
        for (; l1 != nullptr || l2 != nullptr; l1 = l1 != nullptr ? l1->next : l1, l2 = l2 != nullptr ? l2->next: l2)
        {
            int sum = (l1 != nullptr ? l1->val : 0) + (l2 != nullptr ? l2->val : 0) + carry;
            carry = sum / 10;
            
            *insertion_point = new ListNode(sum % 10);
            insertion_point = &(*insertion_point)->next;
        }
        
        if (carry != 0 || head == nullptr)
            *insertion_point = new ListNode(carry);
            
        return head;
    }
};
