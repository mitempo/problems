// https://leetcode.com/problems/reverse-linked-list-ii/description/

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
    ListNode*& advance(ListNode*& l, int m)
    {
        ListNode **p = &l;
        
        while (*p != nullptr && m--)
            p = &(*p)->next;
        
        return *p;
    }
    
    void reverse(ListNode*& l, int m)
    {
        if (m < 2 || l == nullptr) return;
        
        ListNode*& lastnext = l->next;
        
        ListNode *r = nullptr;
        
        while (l != nullptr && m--)
        {
            auto t = r;
            r = l;
            l = l->next;
            r->next = t;
        }
        
        lastnext = l;
        l = r;
    }
        
    ListNode* reverseBetween(ListNode* head, int m, int n) {
        ListNode*& start = advance(head, m - 1);
        reverse(start, n - m + 1);
        return head;
    }
};
