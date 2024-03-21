#pragma once
#include "..\Common.h"

// https://leetcode.com/problems/reverse-linked-list/
/*
        1   ->   2   ->   3   ->   4   ->   5

        1        2   ->   3   ->   4   ->   5
        prev     head->   3   ->   4   ->   5

        1   <-   2        3   ->   4   ->   5
                 prev     head

        1   <-   2   <-   3        4   ->   5
                          prev     head

        1   <-   2   <-   3   <-   4        5
                                   prev     head

        1   <-   2   <-   3   <-   4   <-   5
                                            prev (return)
*/
ListNode* reverseList(ListNode* head) {
    if (!head || !head->next) {
        return head;
    }

    ListNode* prev = nullptr;
    while (head) {
        ListNode* next = head->next;
        head->next = prev;
        prev = head;
        head = next;
    }
    return prev;
}

// https://leetcode.com/problems/reverse-linked-list-ii/
ListNode* reverseBetween(ListNode* head, int left, int right) {
    // lead -> start..end -> tail
    ListNode* sentinel = new ListNode(0, head);
    ListNode* lead = sentinel;
    for (int i = 1; i < left; ++i) {
        lead = lead->next;
    }

    // now revert start..end
    ListNode* start = lead->next; // we need to set start->next = tail
    ListNode* end = nullptr; // when we reach the end, note it down, since we need to set prev->next = last
    ListNode* prev = lead;
    ListNode* iter = start;
    for (int i = left; i <= right; ++i) {
        if (i == right) {
            end = iter;
        }
        ListNode* next = iter->next;
        iter->next = prev;
        prev = iter;
        iter = next;
    } // now iter points to one past end, i.e., tail

    start->next = iter;
    lead->next = end;

    return sentinel->next;
}
