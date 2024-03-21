#pragma once
#include "..\Common.h"

// https://leetcode.com/problems/merge-two-sorted-lists/
ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
    ListNode* sentinel = new ListNode();
    ListNode* prev = sentinel;

    while (list1 || list2) {
        if (!list2 || (list1 && list1->val < list2->val)) {
            prev->next = list1;
            list1 = list1->next;
        }
        else {
            prev->next = list2;
            list2 = list2->next;
        }
        prev = prev->next;
    }

    return sentinel->next;
}
