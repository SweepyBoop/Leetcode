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
