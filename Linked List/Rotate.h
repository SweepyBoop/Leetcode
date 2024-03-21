#pragma once
#include "..\Common.h"

// https://leetcode.com/problems/rotate-list/
ListNode* rotateRight(ListNode* head, int k) {
    // 1  ->  2  ->  3  ->  4  ->  5, k = 2
    // head          pivot  next   last (last is k nodes ahead of pivot)
    // 4  ->  5  ->  1  ->  2  ->  3
    // next          head          pivot

    // we can find pivot / last and list size n in one iteration using 2 pointers
    ListNode* pivot = head;
}
