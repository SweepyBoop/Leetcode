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

bool isSymmetricIterative(TreeNode* root) {
    if (!root) {
        return true;
    }

    if (!root->left && !root->right) {
        return true;
    }

    if (!root->left || !root->right) {
        return false;
    }

    // this is similar to a level order traversal, but each time we pop 2 nodes n1 and n2, and check if they are the same
    // when pushing their children, push like this:
    // n1.left, n2.right, n1.right, n2.left

    // level order traversal uses a queue
    queue<TreeNode*> q;
    q.push(root->left);
    q.push(root->right);

    while (!q.empty()) {
        int levelSize = q.size();
        while (levelSize) {
            TreeNode* left = q.front();
            q.pop();
            TreeNode* right = q.front();
            q.pop();
            levelSize -= 2;

            if (left->val != right->val) {
                return false;
            }

            if ((left->left == nullptr) ^ (right->right == nullptr)) {
                return false;
            }

            if (left->left) {
                q.push(left->left);
                q.push(right->right);
            }

            if ((left->right == nullptr) ^ (right->left == nullptr)) {
                return false;
            }

            if (left->right) {
                q.push(left->right);
                q.push(right->left);
            }
        }
    }

    return true;
}
