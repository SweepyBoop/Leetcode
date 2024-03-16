#pragma once
#include "..\Common.h"

int destroyTargets(vector<int>& nums, int space) {
    // keep track of nums[i] % space
    // elements that can be destroyed share the same remainder
    // we want to find which remainder has the most elements, then find out the smallest element that belongs to a group with mostElements
    unordered_map<int, int> remainderMap;
    int mostElements = 0; // most elements held in a remainder group, 2 groups could have the same elements
    for (int num : nums) {
        int remainder = num % space;
        ++remainderMap[remainder];
        if (remainderMap[remainder] > mostElements) {
            mostElements = remainderMap[remainder];
        }
    }

    // now iterate through nums again, if a num belongs to a remainder group with the most elements, it is potentially an answer
    // we still need to find the smallest value
    int ans = INT_MAX;
    for (int num : nums) {
        if (remainderMap[num % space] == mostElements) {
            ans = min(ans, num);
        }
    }
    return ans;
}