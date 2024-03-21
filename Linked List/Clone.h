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
