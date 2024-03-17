#pragma once
#include "..\Common.h"

int takeCharacters(string s, int k) {
    // sliding window [i..j] in the middle for chars we don't take
    // when i slides left, exclude one more char
    // when j slides left, include one more char

    unordered_map<char, int> counts;
    
    // first check if a solution exists
    for (auto ch : s) {
        ++counts[ch];
    }

    if (counts['a'] < k || counts['b'] < k || counts['c'] < k) {
        return -1;
    }

    int n = s.length();
    int windowSize = 0;
    // s[left..right] is what we exclude, find the biggest exclude window s.t. the remaining part is valid
    // start from excluding nothing
    int left = 0;
    int right = 0;
    while (right < n) { // when right reaches the end, we can't make the exclude window any bigger
        --counts[s[right]];
        // by newly excluding s[right], the window could become invalid, make it valid again
        while (counts['a'] < k || counts['b'] < k || counts['c'] < k) {
            ++counts[s[left]]; // remove left from the window
            ++left;
        }

        // now [left..right] is a valid exclude window, the ans is the n - exclude window size
        // what happens if we can't exclude anything, then left goes one char beyond right, we get windowSize = 0
        windowSize = max(windowSize, right - left + 1);

        ++right;
    }

    return n - windowSize;
}
