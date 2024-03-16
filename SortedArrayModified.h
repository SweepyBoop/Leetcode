#pragma once

#include <vector>
using namespace std;

// https://leetcode.com/problems/squares-of-a-sorted-array/
vector<int> sortedSquares(vector<int>& nums) {
    // notice the pattern the modified array is a descending + ascending array
    // we can use 2 pointers to get a descending array
    int n = nums.size();
    for (int i = 0; i < n; ++i) {
        nums[i] = nums[i] * nums[i];
    }

    vector<int> ans(n, 0);
    int left = 0;
    int right = n - 1;
    // there are 2 ways to check when to end iterations
    //   a. left meets right
    //   b. we need exactly n iterations

    // because we are iterating from large values, assign them starting from the end of the ans array
    for (int i = n - 1; i >= 0; --i) {
        if (nums[left] < nums[right]) {
            ans[i] = nums[right--];
        }
        else {
            ans[i] = nums[left++];
        }
    }
    return ans;
}