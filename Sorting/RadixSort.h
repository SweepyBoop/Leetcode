#pragma once
#include "..\Common.h"

#define NUM_DIGITS 10

// Radix sort leverages counting sort, it is basically a counting sort on each digit
// This works because counting sort is a stable sort (relative order of elements remain unchanged)
// There are 2 ways to do a counting sort
//     a. Use a starting index for each digit
//     b. Use a vector of vector to store the numbers for each digit

void countingSort_StartingIndex(vector<int>& nums, int placeVal) {
    vector<int> counts(NUM_DIGITS, 0);

    for (int element : nums) {
        int digit = abs(element) / placeVal % NUM_DIGITS;
        ++counts[digit];
    }

    // modify counts into starting index for each value
    int startingIndex = 0;
    for (int i = 0; i < counts.size(); ++i) {
        int count = counts[i];
        counts[i] = startingIndex;
        startingIndex += count;
    }

    vector<int> sortedArray(nums.size(), 0);
    for (int element : nums) {
        int digit = abs(element) / placeVal % NUM_DIGITS;
        // put this value to the appropriate index
        sortedArray[counts[digit]] = element;
        ++counts[digit];
    }

    // assign the elements back to the original array
    for (int i = 0; i < nums.size(); ++i) {
        nums[i] = sortedArray[i];
    }
}

// This uses a vector of vector to store elements for each digit
// It's also considering negative values (we need to reverse it afterwards)
// More straightforward, but more memory (vector of vector to store original elements)
void countingSort_Bucket(vector<int>& array, int placeVal) {
    vector<vector<int>> mapDigits(NUM_DIGITS, vector<int>());
    for (int& num : array) {
        int digit = abs(num) / placeVal % NUM_DIGITS;
        mapDigits[digit].push_back(num);
    }

    // Overwrite 'array' in sorted order of current place digits.
    int index = 0;
    for (int digit = 0; digit < NUM_DIGITS; ++digit) {
        for (int& num : mapDigits[digit]) {
            array[index++] = num;
        }
    }
}

// https://leetcode.com/problems/sort-transformed-array/
vector<int> sortTransformedArray(vector<int>& nums, int a, int b, int c) {
    int n = nums.size();

    // calculate and find the max abs value along the way
    int maxAbs = 0;
    for (int i = 0; i < n; ++i) {
        int num = nums[i];
        nums[i] = a * num * num + b * num + c;
        maxAbs = max(maxAbs, abs(nums[i]));
    }

    // radix sort (from LSD to highest)
    int placeVal = 1;
    while (maxAbs / placeVal > 0) {
        countingSort_Bucket(nums, placeVal);
        placeVal *= 10;
    }

    // we are sorted by abs, but there are negative values
    vector<int> positives;
    vector<int> negatives;
    for (int& num : nums) {
        if (num < 0) {
            negatives.push_back(num);
        }
        else {
            positives.push_back(num);
        }
    }

    // need to reverse the negatives
    reverse(negatives.begin(), negatives.end());

    // now merge positives and negatives
    vector<int> ans(n, 0);
    merge(negatives.begin(), negatives.end(), positives.begin(), positives.end(), ans.begin());
    return ans;
}
