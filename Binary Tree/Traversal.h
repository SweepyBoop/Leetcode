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

        // we have visited the node and its left sub tree
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

void printPostOrderIterativeTwoStacks(TreeNode* root) {
    // similar to preorder, but instead of printing it, push it to a second stack
    // the second stack will store the post order nodes in reverse
    if (!root) {
        return;
    }

    stack<TreeNode*> stack1;
    stack1.push(root);
    stack<TreeNode*> stack2;

    while (!stack1.empty()) {
        TreeNode* pop = stack1.top();
        stack1.pop();
        stack2.push(pop);

        if (pop->left) {
            stack1.push(pop->left);
        }

        if (pop->right) {
            stack1.push(pop->right);
        }
    }

    while (!stack2.empty()) {
        TreeNode* pop = stack2.top();
        stack2.pop();
        cout << pop->val << " ";
    }
}

// https://leetcode.com/problems/binary-tree-level-order-traversal/
// BFS traveral
vector<vector<int>> levelOrder(TreeNode* root) {
    vector<vector<int>> ans;

    if (!root) {
        return ans;
    }

    queue<TreeNode*> q;
    q.push(root);

    while (!q.empty()) {
        vector<int> currentLevel;

        // how many nodes at current level
        int currentLevelSize = q.size();

        while (currentLevelSize--) {
            TreeNode* node = q.front();
            q.pop();

            currentLevel.push_back(node->val);

            if (node->left) {
                q.push(node->left);
            }

            if (node->right) {
                q.push(node->right);
            }
        }

        ans.push_back(currentLevel);
    }

    return ans;
}

// https://leetcode.com/problems/binary-tree-level-order-traversal-ii/
// just reverse the array before returning

// https://leetcode.com/problems/binary-tree-zigzag-level-order-traversal/
// just reverse the odd index levels (level[1], level[3], etc.)
