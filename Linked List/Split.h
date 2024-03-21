#pragma once
#include "..\Common.h"

// https://leetcode.com/problems/partition-list/description/?envType=study-plan-v2&envId=top-interview-150
ListNode* partition(ListNode* head, int x) {
    ListNode* sentinel_left = new ListNode();
    ListNode* sentinel_right = new ListNode();

    ListNode* prev_left = sentinel_left;
    ListNode* prev_right = sentinel_right;

    while (head) {
        // cut next to avoid circles in the result list
        ListNode* next = head->next;
        head->next = nullptr;

        if (head->val < x) {
            prev_left->next = head;
            prev_left = prev_left->next;
        }
        else {
            prev_right->next = head;
            prev_right = prev_right->next;
        }

        head = next;
    }

    // now we have sentinel_left -> left list, sentinel_right -> right list
    // and prev_left points to the last node in left list
    if (prev_left) {
        prev_left->next = sentinel_right->next;
    }

    return sentinel_left->next;
}
