#pragma once
#include "..\Common.h"

// https://leetcode.com/problems/add-two-numbers/description/
ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
    ListNode* sentinel = new ListNode();
    ListNode* iter = sentinel;
    int carryover = 0;
    while (l1 || l2 || carryover) {
        int tmp = (l1 ? l1->val : 0) + (l2 ? l2->val : 0) + carryover;
        int digit = tmp % 10;
        carryover = tmp / 10;
        iter->next = new ListNode(digit);
        iter = iter->next;

        if (l1) {
            l1 = l1->next;
        }
        if (l2) {
            l2 = l2->next;
        }
    }

    return sentinel->next;
}
