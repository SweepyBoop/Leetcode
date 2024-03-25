#pragma once
#include "..\Common.h"

// https://leetcode.com/problems/invert-binary-tree/
TreeNode* invertTree(TreeNode* root) {
    if (!root) {
        return root;
    }

    TreeNode* invertedRight = invertTree(root->right);
    TreeNode* invertedLeft = invertTree(root->left);
    root->left = invertedRight;
    root->right = invertedLeft;
    return root;
}

TreeNode* invertTreeIterative(TreeNode* root) {
    if (!root) {
        return root;
    }

    // keep nodes that haven't been inverted
    stack<TreeNode*> s;
    s.push(root);
    while (!s.empty()) {
        TreeNode* node = s.top();
        s.pop();

        TreeNode* tmp = node->left;
        node->left = node->right;
        node->right = tmp;

        if (node->left) {
            s.push(node->left);
        }

        if (node->right) {
            s.push(node->right);
        }
    }

    return root;
}
