#pragma once
#include "..\Common.h"

// https://leetcode.com/problems/linked-list-cycle/description/?envType=study-plan-v2&envId=top-interview-150
bool hasCycle(ListNode* head) {
    // fast & slow runner, if the list has a cycle, they will meet at some point
    if (!head || !head->next || !head->next->next) {
        return false;
    }

    ListNode* slow = head;
    ListNode* fast = head;
    while (fast->next && fast->next->next) {
        slow = slow->next;
        fast = fast->next->next;

        if (slow == fast) {
            return true;
        }
    }

    return false;
}

// https://leetcode.com/problems/linked-list-cycle-ii/description/
ListNode* detectCycle(ListNode* head) {
    // hash table to store visited nodes, if we encounter it again, it's the beginning of the cycle
    unordered_set<ListNode*> visited;
    while (head) {
        if (visited.find(head) != visited.end()) {
            return head;
        }

        visited.insert(head);
        head = head->next;
    }

    return nullptr;
}
