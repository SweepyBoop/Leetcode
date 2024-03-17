#pragma once
#include "..\Common.h"

// https://leetcode.com/problems/merge-intervals/
vector<vector<int>> merge(vector<vector<int>>& intervals) {
    // sort by starting point
    sort(intervals.begin(), intervals.end());

    // iterate through the list of intervals
    vector<vector<int>> merged;
    for (auto interval : intervals) {
        // if this is the first interval or if this doesn't overlaps with previous in the merged list
        if (merged.empty() || interval[0] > merged.back()[1]) {
            merged.push_back(interval);
        }
        else {
            // merge prev and current into a new interval
            // can interval have a smaller start than prev? no
            merged.back()[1] = max(merged.back()[1], interval[1]);
        }
    }
    return merged;
}