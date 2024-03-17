#pragma once
#include "..\Common.h"

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

    // dp[i] max money if robbing nums[i]
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