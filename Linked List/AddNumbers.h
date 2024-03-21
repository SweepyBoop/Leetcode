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

// https://leetcode.com/problems/add-two-numbers-ii/
ListNode* addTwoNumbersII(ListNode* l1, ListNode* l2) {
    ListNode* r1 = reverseList(l1);
    ListNode* r2 = reverseList(l2);

    // note the direction we're constructing the result list, higher digit->next = prev digit
    ListNode* prevDigit = nullptr;
    int carryover = 0;
    while (r1 || r2 || carryover) {
        int tmp = (r1 ? r1->val : 0) + (r2 ? r2->val : 0) + carryover;
        int digit = tmp % 10;
        carryover = tmp / 10;
        ListNode* currentDigit = new ListNode(digit, prevDigit);
        prevDigit = currentDigit;

        if (r1) {
            r1 = r1->next;
        }

        if (r2) {
            r2 = r2->next;
        }
    }
    return prevDigit;
}