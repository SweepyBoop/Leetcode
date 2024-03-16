#pragma once
#include "..\Common.h"

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

// https://leetcode.com/problems/sort-transformed-array/description/
vector<int> sortTransformedArray(vector<int>& nums, int a, int b, int c) {
    int n = nums.size();
    for (int i = 0; i < n; ++i) {
        int num = nums[i];
        nums[i] = a * num * num + b * num + c;
    }

    // if a == 0, then we have a straight line
    // if a < 0, we have asc + desc array; if a > 0, we have desc + asc array
    // use 2 pointers to iterate elements
    vector<int> ans(n, 0);
    int left = 0;
    int right = n - 1;
    if (a < 0) {
        // we are going from smallest element
        // since we need exactly n iterations, we can use that to determine iteration end instead of left meeting right
        for (int i = 0; i < n; ++i) {
            if (nums[left] < nums[right]) {
                ans[i] = nums[left++];
            }
            else {
                ans[i] = nums[right--];
            }
        }
    }
    else {
        // we are going from largest element, therefore need to reverse at the end
        // this includes the case where a == 0, regardless of b value, we're going from largest value
        for (int i = n - 1; i >= 0; --i) {
            if (nums[left] < nums[right]) {
                ans[i] = nums[right--];
            }
            else {
                ans[i] = nums[left++];
            }
        }
    }
}
