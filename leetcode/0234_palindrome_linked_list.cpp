// https://leetcode.com/problems/palindrome-linked-list/description/

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
using List = ListNode *;

class Solution {
public:
    int len(List l)
    {
        int s = 0;
        for (; l != nullptr; l = l->next)
            ++s;
        return s;
    }
    
    void reverse(List& l)
    {
        List r = nullptr;
        
        while (l != nullptr)
        {
            List t = r;
            r = l;
            l = l->next;
            r->next = t;
        }
        
        l = r;
    }
    
    List& advance(List& l, int n)
    {
        List *p = &l;
        while (n-- && *p != nullptr) p = &(*p)->next;
        return *p;
    }
    
    bool isPalindrome(List head) {
        int llen = len(head);
        if (llen < 2) return true;
        
        List& shalf = advance(head, llen / 2);
        reverse(shalf);

        List shf = shalf;
        shalf = nullptr;
        
        for (; head != nullptr && shf != nullptr; head = head->next, shf = shf->next)
            if (head->val != shf->val)
                return false;

        return true;
    }
};
