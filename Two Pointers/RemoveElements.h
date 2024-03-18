#pragma once
#include "..\Common.h"

// https://leetcode.com/problems/remove-element/description/?envType=study-plan-v2&envId=top-interview-150
int removeElement(vector<int>& nums, int val) {
    // squeeze elements to be removed to the end of the array
    // keep 2 pointers:
    //   1. from left -> right for iterating
    //   2. from right -> left to mark the last kept pos
    int iter = 0;
    int lastPos = nums.size() - 1;

    while (iter <= lastPos) {
        while (nums[iter] == val && iter <= lastPos) {
            // the new element swapped from the end might still need to be removed
            swap(nums[iter], nums[lastPos]);
            --lastPos;
        }
        ++iter;
    }
    return lastPos + 1;
}

// https://leetcode.com/problems/remove-duplicates-from-sorted-array/description/?envType=study-plan-v2&envId=top-interview-150
int removeDuplicates(vector<int>& nums) {
    // 2 pointers: one for iteration, one for last used pos
    int used = -1;
    for (int i = 0; i < nums.size(); ++i) {
        if (i == 0 || nums[i] != nums[used]) {
            nums[++used] = nums[i];
        }
    }
    return used + 1;
}

// https://leetcode.com/problems/remove-duplicates-from-sorted-array-ii/
// can be generalized to each element appears at most k times

//this will not work, we need to check i against the index where the same value appeared for the first time
/*
int remoteDuplicates_wrong(vector<int>& nums, int k) {
    // instead of comparing with previous element, compare with nums[i-k]
    int used = -1;
    for (int i = 0; i < nums.size(); ++i) {
        if (i < k || nums[i] != nums[i - k]) {
            nums[++used] = nums[i];
        }
    }
    return used + 1;
}
*/

int removeDuplicates(vector<int>& nums, int k) {
    int used = -1;
    int currentVal = 0;
    // if we encounter an element == currentVal, we can still keep it if index < firstIndexOfCurrentVal + k
    int firstIndexOfCurrentVal = 0;
    for (int i = 0; i < nums.size(); ++i) {
        if (i == 0 || nums[i] != currentVal) { // a new value, we can safely use it
            nums[++used] = nums[i];
            currentVal = nums[i];
            firstIndexOfCurrentVal = i;
        }
        else { // we have seen this value before
            if (i < firstIndexOfCurrentVal + k) {
                nums[++used] = nums[i];
            }
        }
    }

    return used + 1;
}
