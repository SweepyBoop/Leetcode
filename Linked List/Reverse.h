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

// https://leetcode.com/problems/reverse-nodes-in-k-group/description/?envType=study-plan-v2&envId=top-interview-150
ListNode* reverseKGroup(ListNode* head, int k) {
    // we need to do n / k operations, e.g., n = 5, k = 2, then 2 reverse of size 2
    int n = 0;
    ListNode* iter = head;
    while (iter) {
        ++n;
        iter = iter->next;
    }

    // each iteration: lead -> start..end -> tail (start..end) has k nodes
    //               =>lead -> end..start -> tail
    ListNode* sentinel = new ListNode(0, head);
    ListNode* lead = sentinel;
    ListNode* start = lead->next; // need to start->next = tail
    ListNode* end = nullptr;      // need to lead->next = end

    for (int i = 0; i < n / k; ++i) { // each iteration reverses k nodes from start to end
        ListNode* prev = lead;
        ListNode* iter = start;

        for (int j = 1; j <= k; ++j) {
            if (j == k) { // need to note it down to set lead->next = end
                end = iter;
            }
            ListNode* next = iter->next;
            iter->next = prev;
            prev = iter;
            iter = next;
        } // now iter points to end past 1, i.e., tail

        lead->next = end;
        start->next = iter;

        // set lead, start, end for next iteration
        lead = start;
        start = iter;
    }

    return sentinel->next;
}
