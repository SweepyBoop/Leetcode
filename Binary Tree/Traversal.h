#pragma once
#include "..\Common.h"

// https://www.geeksforgeeks.org/tree-traversals-inorder-preorder-and-postorder/

// The DFS strategy can be further distinguished as preorder DFS, inorder DFS and postorder DFS
// depending on the relative order of visit among the node itself and its child nodes.

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

        if (pop->right) {
            s.push(pop->right);
        }

        if (pop->left) {
            s.push(pop->left);
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

// https://leetcode.com/problems/binary-tree-vertical-order-traversal/
// still BFS with a queue, but need to keep track of columns
// root has column 0, root->left: -1, root->right: 1, etc.
vector<vector<int>> verticalOrder(TreeNode* root) {
    vector<vector<int>> ans;
    if (!root) {
        return ans;
    }

    map<int, vector<int>> columns;
    queue<pair<TreeNode*, int>> q; // track column for every node
    q.push({ root, 0 });

    int minColumn = 0;
    int maxColumn = 0;
    while (!q.empty()) {
        int levelSize = q.size();

        while (levelSize--) {
            auto front = q.front();
            auto node = front.first;
            auto column = front.second;
            q.pop();

            columns[column].push_back(node->val);
            minColumn = min(minColumn, column);
            maxColumn = max(maxColumn, column);

            if (node->left) {
                q.push({ node->left, column - 1 });
            }

            if (node->right) {
                q.push({ node->right, column + 1 });
            }
        }
    }

    for (int i = minColumn; i <= maxColumn; ++i) {
        if (!columns[i].empty()) {
            ans.push_back(columns[i]);
        }
    }
    return ans;
}

// https://leetcode.com/problems/same-tree/
// can do a DFS preorder traversal, be careful to not only check the value but also structure of each node
bool isSameTree(TreeNode* p, TreeNode* q) {
    if (!p && !q) {
        return true;
    }

    if (!p || !q) {
        return false;
    }

    stack<pair<TreeNode*, TreeNode*>> s;
    s.push({ p, q });
    while (!s.empty()) {
        auto top = s.top();
        auto a = top.first;
        auto b = top.second;
        s.pop();

        if (a->val != b->val) {
            return false;
        }

        if ((a->left == nullptr) ^ (b->left == nullptr)) {
            // either both have left child or neither
            return false;
        }

        if (a->left) {
            s.push({ a->left, b->left });
        }

        if ((a->right == nullptr) ^ (b->right == nullptr)) {
            // either both have left child or neither
            return false;
        }

        if (a->right) {
            s.push({ a->right, b->right });
        }
    }

    return true;
}
