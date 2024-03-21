#pragma once
#include "..\Common.h"

// https://leetcode.com/problems/copy-list-with-random-pointer/
class Node {
public:
    int val;
    Node* next;
    Node* random;

    Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};

Node* copyRandomList(Node* head) {
    // create a cloned node as we iterate, keep track of original->cloned with a map
    unordered_map<Node*, Node*> mapping;
    Node* iter = head;
    while (iter) {
        mapping[iter] = new Node(iter->val);
        iter = iter->next;
    }

    iter = head;
    while (iter) {
        mapping[iter]->next = mapping[iter->next];
        mapping[iter]->random = mapping[iter->random];
        iter = iter->next;
    }
    return mapping[head];
}

Node* copyRandomListImproved(Node* head) {
    // A->B->C->D
    // interwined with original nodes
    // A->A'->B->B'->C->C'->D->D'
    Node* iter = head;
    while (iter) {
        Node* next = iter->next;
        Node* clone = new Node(iter->val);
        iter->next = clone;
        clone->next = next;

        iter = next;
    }

    // set the random pointers, now each original's next is always the cloned node
    iter = head;
    while (iter) {
        Node* clone = iter->next;
        Node* next = clone->next;

        if (iter->random) {
            clone->random = iter->random->next;
        }

        iter = next;
    }

    // now we no longer need original->next to locate the cloned nodes
    // set next pointers for the cloned list
    // and restore the next pointers for the original list
    Node* sentinel = new Node(0);
    Node* prev = sentinel;
    while (head) {
        Node* clone = head->next;
        Node* next = clone->next;

        if (next) {
            clone->next = next->next;
        }

        head->next = next;
        head = next;

        // construct result list
        prev->next = clone;
        prev = prev->next;
    }

    return sentinel->next;
}
