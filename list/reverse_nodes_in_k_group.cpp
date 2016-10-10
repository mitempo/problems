// https://leetcode.com/problems/reverse-nodes-in-k-group/

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
 
class Solution {
private:
    using List = ListNode *;

public:
    ListNode* reverseKGroup(ListNode* head, int k)
    {
        if (head == nullptr) return nullptr;

        List *pCur = &head;

        for ( ; ; )
        {
            List *pNext = &(*pCur)->next; 
            
            List *pLimit = advanceK(*pCur, k);
            if (pLimit == nullptr) break;

            reverseTill(*pCur, *pLimit);
            pCur = pNext;
        }
        
        return head;
    }

    List *advanceK(List& list, int k)
    {
        return k == 0          ? &list :
               list == nullptr ? nullptr :
                                 advanceK(list->next, k - 1);
    }

    void reverseTill(List& list, List end)
    {
        List result = end;

        while (list != end)
        {
            List next = list->next;
            list->next = result;
            result = list;
            list = next;
        }
        
        list = result;
    }
};
