#pragma once
#include "..\Common.h"

// https://leetcode.com/problems/flatten-binary-tree-to-linked-list/

// flatten root and return the tail node
TreeNode* flattenHelper(TreeNode* root) {
    if (!root) {
        return nullptr;
    }

    if (!root->left && !root->right) {
        return root;
    }

    TreeNode* leftTail = flattenHelper(root->left);
    TreeNode* rightTail = flattenHelper(root->right);

    if (leftTail) {
        leftTail->right = root->right;
        root->right = root->left;
        root->left = nullptr;
    }

    return rightTail ? rightTail : leftTail;
}

void flatten(TreeNode* root) {
    flattenHelper(root);
}

// Use a stack, this is basically a preorder traversal
void flatten(TreeNode* root) {
    if (!root) {
        return;
    }

    TreeNode* prev = nullptr;
    stack<TreeNode*> s;
    s.push(root);
    while (!s.empty()) {
        TreeNode* top = s.top();
        s.pop();
        if (top->right) {
            s.push(top->right);
        }
        if (top->left) {
            s.push(top->left);
        }

        if (prev) {
            prev->right = top;
            prev->left = nullptr;
        }

        prev = top;
    }
}

// O(1) solution
void flatten(TreeNode* root) {
    if (!root) {
        return;
    }

    TreeNode* curr = root;
    while (curr) {
        // if curr has a left child, find the rightmost node of its left subtree
        if (curr->left) {
            TreeNode* rightmost = curr->left;
            while (rightmost && rightmost->right) {
                rightmost = rightmost->right;
            }


        }
    }
}
