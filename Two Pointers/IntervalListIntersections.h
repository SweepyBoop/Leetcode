#pragma once
#include "..\Common.h"

// https://leetcode.com/problems/interval-list-intersections/
vector<vector<int>> intervalIntersection(vector<vector<int>>& firstList, vector<vector<int>>& secondList) {
    // use 2 pointers, and always pick the interval with lowest end point, it would only intersect with one interval from the other
    // why would this work? Imaging the following case:
    // A: [0                     10]
    // B:   [1    3]   [4.............12]
    // Pick [1...3] then it only intersects with [1...10]
    // Then pick [1...10] then it only intersects with [4...12]
    int n1 = firstList.size();
    int n2 = secondList.size();
    int left = 0;
    int right = 0;
    vector<vector<int>> ans;


    while (left < n1 && right < n2) {
        if (firstList[left][1] < secondList[right][1]) {
            // check the interval on the first list and see if it intersects with current interval on the second list
            if (firstList[left][1] >= secondList[right][0]) {
                vector<int> interval;
                // we take the bigger start point between the 2 intervals on both lists
                int start = max(firstList[left][0], secondList[right][0]);
                interval.push_back(start);
                interval.push_back(firstList[left][1]);
                ans.push_back(interval);
            }
            ++left;
        }
        else {
            if (secondList[right][1] >= firstList[left][0]) {
                vector<int> interval;
                int start = max(firstList[left][0], secondList[right][0]);
                interval.push_back(start);
                interval.push_back(secondList[right][1]);
                ans.push_back(interval);
            }
            ++right;
        }
    }

    return ans;
}