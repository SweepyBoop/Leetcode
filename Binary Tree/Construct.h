#pragma once
#include "..\Common.h"

// https://leetcode.com/problems/construct-binary-tree-from-preorder-and-inorder-traversal/

// build tree from preorder[pl..pr], inorder[il..ir]
// to find the index of the root from inorder, use a hash table
TreeNode* buildTreeHelper(unordered_map<int, int>& inorderIndex, vector<int>& preorder, vector<int>& inorder, int pl, int pr, int il, int ir) {
    if (pr < 0 || pr >= preorder.size()) {
        return nullptr;
    }

    // the first element in the preorder array is the root element
    int rootVal = preorder[pl];
    TreeNode* root = new TreeNode(rootVal);

    int rootInorderIndex = inorderIndex[rootVal];

    // number of elements on two sides of the inorder array for left/right sub tree
    int leftSize = rootInorderIndex - il;
    int rightSize = ir - rootInorderIndex;
    if (leftSize) {
        root->left = buildTreeHelper(inorderIndex, preorder, inorder, pl + 1, pl + leftSize, il, rootInorderIndex - 1);
    }
    if (rightSize) {
        root->right = buildTreeHelper(inorderIndex, preorder, inorder, pl + leftSize + 1, pr, rootInorderIndex + 1, ir);
    }
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

// https://leetcode.com/problems/construct-binary-tree-from-inorder-and-postorder-traversal/
TreeNode* buildTreeHelperII(unordered_map<int, int>& inorderIndex, vector<int>& inorder, vector<int>& postorder, int il, int ir, int pl, int pr) {
    if (pr < 0 || pr >= postorder.size()) {
        return nullptr;
    }

    // the last element in postorder is the root
    int rootVal = postorder[pr];
    TreeNode* root = new TreeNode(rootVal);

    int rootInorderIndex = inorderIndex[rootVal];
    int leftSize = rootInorderIndex - il;
    int rightSize = ir - rootInorderIndex;
    if (leftSize) {
        root->left = buildTreeHelperII(inorderIndex, inorder, postorder, il, rootInorderIndex - 1, pl, pl + leftSize - 1);
    }
    if (rightSize) {
        root->right = buildTreeHelperII(inorderIndex, inorder, postorder, rootInorderIndex + 1, ir, pl + leftSize, pr - 1);
    }
    return root;
}

TreeNode* buildTreeII(vector<int>& inorder, vector<int>& postorder) {
    int n = inorder.size();
    unordered_map<int, int> inorderIndex;
    for (int i = 0; i < n; ++i) {
        inorderIndex[inorder[i]] = i;
    }

    return buildTreeHelperII(inorderIndex, inorder, postorder, 0, n - 1, 0, n - 1);
}
