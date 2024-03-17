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