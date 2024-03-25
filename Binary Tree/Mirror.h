#pragma once
#include "..\Common.h"

// https://leetcode.com/problems/symmetric-tree/
//      root
//     /    \
//   left   right
//  /   \   /  \
// X    Y   Y   X
// base case: left and right are leaf nodes with the same value
// recursive: (left.val == right.val) && isMirror(left.left, right.right) && isMirror(left.right, right.left)

bool isMirror(TreeNode* left, TreeNode* right) {
    if (!left && !right) {
        return true;
    }

    if (!left || !right) {
        return false;
    }

    return (left->val == right->val)
        && isMirror(left->left, right->right)
        && isMirror(left->right, right->left);
}

bool isSymmetric(TreeNode* root) {
    if (!root) {
        return true;
    }

    return isMirror(root->left, root->right);
}
