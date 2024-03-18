#pragma once
#include "..\Common.h"

// https://leetcode.com/problems/majority-element/description/?envType=study-plan-v2&envId=top-interview-150
int majorityElement(vector<int>& nums) {
    // using hash table is trivial, we can improve the space complexity using bitwise manipulation
    // think about binary numbers for [3,2,3]
    // 11
    // 10
    // 11
    // for each digit, we count the frequency of 1, if it appears more than n/2 times, it means the answer has that big set
    int n = nums.size();
    int ans = 0;
    const int size = 32;
    for (int i = 0; i < size; ++i) {
        int count = 0;
        int digit = 1 << i;
        for (int num : nums) {
            if (digit & num) {
                ++count;
            }
        }
        if (count > n / 2) {
            ans |= digit;
        }
    }
    return ans;
}
