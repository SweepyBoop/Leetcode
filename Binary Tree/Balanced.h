#pragma once
#include "..\Common.h"

// https://leetcode.com/problems/balanced-binary-tree/
int treeHeight(TreeNode* root) {
    if (!root) {
        return 0;
    }

    return 1 + max(treeHeight(root->left), treeHeight(root->right));
}

bool isBalanced(TreeNode* root) {
    // definition of balanced tree: given any node, |height(node.left) - height(node.right)| <= 1

    if (!root) {
        return true;
    }

    if (abs(treeHeight(root->left) - treeHeight(root->right)) > 1) {
        return false;
    }

    return isBalanced(root->left) && isBalanced(root->right);
}

// return if root is balanced, and store its height
bool isBalancedHelper(TreeNode* root, int& height) {
    if (!root) {
        height = -1;
        return true;
    }

    int leftHeight{};
    int rightHeight{};
    if (isBalancedHelper(root->left, leftHeight)
        && isBalancedHelper(root->right, rightHeight)
        && abs(leftHeight - rightHeight) < 2) {
        height = max(leftHeight, rightHeight) + 1;
        return true;
    }
    return false;
}

bool isBalancedImproved(TreeNode* root) {
    int height{};
    return isBalancedHelper(root, height);
}
