#pragma once
#include "..\Common.h"

// https://leetcode.com/problems/remove-nth-node-from-end-of-list/?envType=study-plan-v2&envId=top-interview-150
ListNode* removeNthFromEnd(ListNode* head, int n) {
    // nth node from the end
    // head->...->remove..end, end is (n-1) nodes ahead of remove, we can find it using 2 pointers
    // sentinel->head->...->prev->remove..end, end is n nodes ahead of remove
    ListNode* sentinel = new ListNode(0, head);
    ListNode* left = sentinel;
    ListNode* right = left;
    for (int i = 0; i < n; ++i) {
        right = right->next;
    }

    while (right && right->next) {
        left = left->next;
        right = right->next;
    } // now right is the last node, left is the node before removal

    left->next = left->next->next;
    return sentinel->next;
}
