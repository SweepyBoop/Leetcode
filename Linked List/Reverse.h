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
