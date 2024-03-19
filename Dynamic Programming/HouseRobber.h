#pragma once
#include "..\Common.h"

// https://leetcode.com/problems/house-robber/description/

// at each step, there is a decision to be made, whether to rob nums[i]
// a. rob nums[i], then cannot rob nums[i-1], we can take rob(i-2)
// b. don't rob nums[i], then we can take rob(i-1)
// what if rob(i-1) doesn't include nums[i-1]? can't we rob nums[i] and still take rob(i-1)?
// in that case, rob(i-1) will be the same as rob(i-2)

int rob(vector<int>& nums) {
    int n = nums.size();

    if (n == 1) {
        return nums[0];
    }

    // dp[i] max money from robbing nums[0..i]
    vector<int> dp(n, 0);
    dp[0] = nums[0];
    for (int i = 1; i < n; ++i) {
        // if we don't rob current house, max from previous houses is dp[i-1]
        dp[i] = max(dp[i], dp[i - 1]);
        // if we rob current house, max from previous houses is dp[i-2]
        dp[i] = max(dp[i], nums[i] + ((i >= 2) ? dp[i - 2] : 0));
    }

    return dp[n - 1];
}

int rob_constSpace(vector<int>& nums) {
    int n = nums.size();

    if (n == 1) {
        return nums[0];
    }

    //       House House House House
    // prev2 prev1
    //       prev2 prev1
    //             prev2 prev1
    //                   prev2 prev1
    //                         return

    int prev1 = nums[0];
    int prev2 = 0;
    for (int i = 1; i < n; ++i) {
        int tmp = prev1;
        prev1 = max(prev1, nums[i] + prev2);
        prev2 = tmp;
    }
    return prev1;
}

// https://leetcode.com/problems/house-robber-ii/description/
// we can divide this problem into:
// 7 4 1 9 3 8 6 5
// 7 4 1 9 3 8 6   => max1
//   4 1 9 3 8 6 5 => max2
// and return max(max1, max2)

// refactor rob into a function that also takes a range, this range has at least 2 elements
int rob_range(vector<int>& nums, int start, int end) {
    int n = nums.size();

    //       House House House House
    // prev2 prev1
    //       prev2 prev1
    //             prev2 prev1
    //                   prev2 prev1
    //                         return

    int prev1 = nums[start];
    int prev2 = 0;
    for (int i = start + 1; i <= end; ++i) {
        int tmp = prev1;
        prev1 = max(prev1, nums[i] + prev2);
        prev2 = tmp;
    }
    return prev1;
}

int rob_ii(vector<int>& nums) {
    int n = nums.size();
    if (n == 1) {
        return nums[0];
    }

    int max1 = rob_range(nums, 0, n - 2);
    int max2 = rob_range(nums, 1, n - 1);
    return max(max1, max2);
}

// https://leetcode.com/problems/house-robber-iii/description/
// for each node, the decision is:
// a. rob this node, then can't rob either child node
// b. don't rob this node, then can rob either child node
// we can have 2 dp that stores the optimal ans when robbing a node vs. not robbing a node

// but just having one dp works, e.g.,
//       A(3)
//   B(2)     C(3)
//     D(3)     E(1)
// what if we rob top A => we can't rob its children B or C, but dp(B) doesn't rob B anyways?
// then dp(B) = dp(D) as if B wasn't involved in the first place => taking dp(D) is still correct

int robHelper(TreeNode* root, unordered_map<TreeNode*, int>& memory) {
    if (!root) {
        return 0;
    }

    if (memory[root]) {
        return memory[root];
    }

    // if we rob root, then we can't rob root->left or root->right
    int rob = root->val;
    if (root->left) {
        rob += robHelper(root->left->left, memory) + robHelper(root->left->right, memory);
    }
    if (root->right) {
        rob += robHelper(root->right->left, memory) + robHelper(root->right->right, memory);
    }

    // if we don't rob root
    int noRob = robHelper(root->left, memory) + robHelper(root->right, memory);

    int res = max(rob, noRob);
    memory[root] = res;
    return res;
}

int rob(TreeNode* root) {
    unordered_map<TreeNode*, int> memory;
    return robHelper(root, memory);
}