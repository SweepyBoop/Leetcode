#pragma once
#include "..\Common.h"

// https://leetcode.com/problems/minimum-time-to-repair-cars/
// Given x minutes, we can check how many cars can be fixed in total and whether it >= cars
// Do a binary search, but what initial range do we define?
// max rank = 100, max cars = 10^6, so max x = 100 * pow(10^6, 2) = 10^14
long long repairCars(vector<int>& ranks, int cars) {
    int n = ranks.size();
    long long left = 0;
    long long right = 1e14;
    while (left < right) {
        // avoid overflow
        long long mid = left + (right - left) / 2;
        // given mid minutes, how many cars can we repair
        long long repair = 0;
        for (int rank : ranks) {
            repair += sqrt(mid / rank);
        }

        if (repair < cars) {
            left = mid + 1;
        }
        else {
            right = mid;
        }
    }

    return left;
}
