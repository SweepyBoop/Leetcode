#pragma once
#include "..\Common.h"

// https://leetcode.com/problems/maximum-depth-of-binary-tree/description/?envType=study-plan-v2&envId=top-interview-150
// TODO: research "tail recursion"
int maxDepth(TreeNode* root) {
    // use a stack, this will be preorder traversal (root, left, right)
    //          3
    //        /   \
    //       9     20
    //             / \
    //           15   7
    // push 3
    // pop  3, push 9, 20
    // pop 9
    // pop 20, push 15, 7
    // pop 15
    // pop 7
    // order: 3, 9, 20, 15, 7

    if (!root) {
        return 0;
    }

    // each pair contains <depth, node>
    int maxDepth = 0;
    stack<pair<int, TreeNode*>> nodes;
    nodes.push({1, root});
    while (!nodes.empty()) {
        auto top = nodes.top();
        auto depth = top.first;
        auto node = top.second;
        nodes.pop();
        maxDepth = max(maxDepth, depth);
        if (node->left) {
            nodes.push({ depth + 1, node->left });
        }
        if (node->right) {
            nodes.push({ depth + 1, node->right });
        }
    }
    return maxDepth;
}
