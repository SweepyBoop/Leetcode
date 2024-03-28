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

            rightmost->right = curr->right;
            curr->right = curr->left;
            curr->left = nullptr;
        }

        curr = curr->right;
    }
}

/*
    Morris Traversal

           3
         /   \
        1     4
         \
          2
    current = 3
    predecessor = 2, set 2->R = 3, set current = 1
    current = 1, no left child, PRINT(1), set current = 2
    current = 2, no left child, PRINT(2), set current = 2->R = 3
    current = 3, predecessor = 2 and 2->R is set, unset 2->R, PRINT(3), set current = 4
    current = 4, no left child, PRINT(4)
*/
void MorrisTraversal(TreeNode* root) {
    if (!root) {
        return;
    }

    TreeNode* current = root;
    while (current) {
        if (!current->left) {
            cout << current->val << " ";
            current = current->right;
        }
        else {
            // Find the inorder predecessor of current
            TreeNode* predecessor = current->left;
            while (predecessor && predecessor->right) {
                predecessor = predecessor->right;
            }

            // Make current as the right child of its inorder predecessor
            if (!predecessor->right) {
                predecessor->right = current;
                current = current->left;
            }
            else { // revert the changes made in the 'if' part to restore the original tree, i.e., fix the right child of the predecessor
                predecessor->right = nullptr;
                cout << current->val << " ";
                current = current->right;
            }
        }
    }
}
