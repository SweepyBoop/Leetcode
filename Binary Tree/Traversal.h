#pragma once
#include "..\Common.h"

// https://www.geeksforgeeks.org/tree-traversals-inorder-preorder-and-postorder/

// left->root->right
void printInOrder(TreeNode* root) {
    if (!root) {
        return;
    }

    printInOrder(root->left);
    cout << root->val << " ";
    printInOrder(root->right);
}

// iterative solution:
// 1. empty stack S
// 2. current = root
// 3. push current & current = current->left until current == NULL
// 4. if current == NULL and stack not empty then
//    a. pop and print top
//    b. current = pop->right
//    c. go to step 3
void printInOrderIterative(TreeNode* root) {
    stack<TreeNode*> s;
    TreeNode* current = root;
    while (current || !s.empty()) {
        while (current) {
            s.push(current);
            current = current->left;
        }

        current = s.top();
        cout << current->val << " ";
        s.pop();

        // we have visited the node and left sub tree
        current = current->right;
    }
}

void printPreOrder(TreeNode* root) {
    if (!root) {
        return;
    }

    cout << root->val << " ";
    printPreOrder(root->left);
    printPreOrder(root->right);
}

void printPreOrderIterative(TreeNode* root) {
    if (!root) {
        return;
    }

    stack<TreeNode*> s;
    s.push(root);
    while (!s.empty()) {
        TreeNode* pop = s.top();
        cout << pop->val << " ";

        if (pop->left) {
            s.push(pop->left);
        }

        if (pop->right) {
            s.push(pop->right);
        }
    }
}

void printPostOrder(TreeNode* root) {
    if (!root) {
        return;
    }

    printPostOrder(root->left);
    printPostOrder(root->right);
    cout << root->val << " ";
}
