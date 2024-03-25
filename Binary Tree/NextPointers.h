#pragma once
#include "..\Common.h"

// https://leetcode.com/problems/populating-next-right-pointers-in-each-node-ii/

class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node* next;

    Node() : val(0), left(NULL), right(NULL), next(NULL) {}

    Node(int _val) : val(_val), left(NULL), right(NULL), next(NULL) {}

    Node(int _val, Node* _left, Node* _right, Node* _next)
        : val(_val), left(_left), right(_right), next(_next) {}
};

/*
  Using level order traversal is trivial with O(n) space
  Can we use constant space?

  While at each level, establish the next pointers for next level, s.t.
  at current level, we already have next pointers ready to iterate through this level

  Each level is exactly like a linked list
  While working on next level, use a sentinel node to mark the start point (like when we work on a linked list)
  Once current level is done, move to sentinel->next for next level
*/


Node* connect(Node* root) {
    if (!root) {
        return root;
    }

    // root level's next pointers already established, start from next level
    Node* levelStart = root;
    while (levelStart) {
        // used for next level
        Node* sentinel = new Node();
        Node* prev = sentinel;

        // used to go through current level
        Node* curr = levelStart;
        while (curr) {
            // check current node's left and right child
            if (curr->left) {
                prev->next = curr->left;
                prev = prev->next;
            }
            if (curr->right) {
                prev->next = curr->right;
                prev = prev->next;
            }

            curr = curr->next;
        }

        // update levelStart for next level
        levelStart = sentinel->next;
    }

    return root;
}
