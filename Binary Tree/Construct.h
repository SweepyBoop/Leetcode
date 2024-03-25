#pragma once
#include "..\Common.h"

// https://leetcode.com/problems/construct-binary-tree-from-preorder-and-inorder-traversal/

// build tree from preorder[pl..pr], inorder[il..ir]
// to find the index of the root from inorder, use a hash table
TreeNode* buildTreeHelper(unordered_map<int, int>& inorderIndex, vector<int>& preorder, vector<int>& inorder, int pl, int pr, int il, int ir) {
    if (pl < 0 || pr >= preorder.size() || pl > pr) {
        return nullptr;
    }

    // the first element in the preorder array is the root element
    int rootVal = preorder[pl];
    TreeNode* root = new TreeNode(rootVal);

    int rootInorderIndex = inorderIndex[rootVal];

    // number of elements on two sides of the inorder array for left/right sub tree
    int leftSize = rootInorderIndex - il;
    int rightSize = ir - rootInorderIndex;
    root->left = buildTreeHelper(inorderIndex, preorder, inorder, pl + 1, pl + leftSize, il, rootInorderIndex - 1);
    root->right = buildTreeHelper(inorderIndex, preorder, inorder, pl + leftSize + 1, pr, rootInorderIndex + 1, ir);
    return root;
}

TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
    int n = inorder.size();
    unordered_map<int, int> inorderIndex;
    for (int i = 0; i < n; ++i) {
        inorderIndex[inorder[i]] = i;
    }

    return buildTreeHelper(inorderIndex, preorder, inorder, 0, n - 1, 0, n - 1);
}
