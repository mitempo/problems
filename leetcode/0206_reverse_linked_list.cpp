// https://leetcode.com/problems/reverse-linked-list/description/

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
    ListNode* reverseList(ListNode* head) {
        ListNode *r = nullptr;
        while (head != nullptr)
        {
            auto t = r;
            r = head;
            head = head->next;
            r->next = t;
        }
        return r;
    }
};