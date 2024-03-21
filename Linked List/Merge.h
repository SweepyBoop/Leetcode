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

// https://leetcode.com/problems/merge-k-sorted-lists/
ListNode* mergeKLists(vector<ListNode*>& lists) {
    // iterate through all lists and find the one with smallest element
    // terminate when all lists are empty
    // keep track of the index of the list that has the smallest value in each iter
    int n = lists.size();
    ListNode* sentinel = new ListNode();
    ListNode* prev = sentinel;
    while (true) {
        int minIndex = -1; // if no element left, this will be -1 and terminate the loop
        for (int i = 0; i < n; ++i)
        {
            if (minIndex == -1 || (lists[i] && lists[i]->val < lists[minIndex]->val)) {
                minIndex = i;
            }
        }

        if (minIndex == -1) {
            break;
        }

        prev->next = lists[minIndex];
        lists[minIndex] = lists[minIndex]->next;
        prev = prev->next;
    }

    return sentinel->next;
}
