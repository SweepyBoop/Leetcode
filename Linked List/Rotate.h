#pragma once
#include "..\Common.h"

// https://leetcode.com/problems/rotate-list/
ListNode* rotateRight(ListNode* head, int k) {
    if (!head || !head->next || k == 0) {
        return head;
    }

    // 1  ->  2  ->  3  ->  4  ->  5, k = 2
    // head          pivot  next   last (last is k nodes ahead of pivot)
    // last->next = head, pivot->next = nullptr
    //
    // 4  ->  5  ->  1  ->  2  ->  3
    // next   last   head          pivot

    // we can find pivot / last and list size n in one iteration using 2 pointers
    // 1  ->  2  ->  3, k = 3
    //               last, index == 3 (do index [1..k])
    int index = 1;
    ListNode* pivot = head;
    ListNode* last = head;
    while (index <= k && last && last->next) {
        ++index;
        last = last->next;
    } // if k >= n, then this will end early, and index == list size

    if (index <= k) {
        k %= index;

        if (k == 0) { // no need to rotate
            return head;
        }

        last = head;
        for (int i = 0; i < k; ++i) {
            last = last->next;
        }
    }

    while (last && last->next) {
        pivot = pivot->next;
        last = last->next;
    }

    ListNode* newHead = pivot->next;
    pivot->next = nullptr;
    last->next = head;
    return newHead;
}
