#pragma once
#include "..\Common.h"

// lps[i] = the longest proper prefix of pat[0..i] which is also a suffix of pat[0..i]. 
// For the pattern "AAAA", lps[] is [0, 1, 2, 3]
// For the pattern "AAABAAA", lps[] is[0, 1, 2, 0, 1, 2, 3]
vector<int> longestPrefixSuffix(string needle) {
    int n = needle.length();
    vector<int> lps(n, 0);

    int i = 1;
    int prev = 0;
    while (i < n) {
        if (needle[i] == needle[prev]) {
            lps[i++] = ++prev;
        }
        else {
            if (prev == 0) {
                lps[i++] = 0;
            }
            else {
                prev = lps[prev - 1];
            }
        }
    }

    return lps;
}

// https://www.geeksforgeeks.org/longest-prefix-also-suffix/
// Given a string s, find the length of the longest prefix, which is also a suffix. The prefix and suffix should not overlap.
// Input : S = aaaa
// Output: 2

// https://leetcode.com/problems/find-the-index-of-the-first-occurrence-in-a-string/description/?envType=study-plan-v2&envId=top-interview-150
int strStr(string haystack, string needle) {
    // KMP is similar to generating LPS
    int haystackLen = haystack.length();
    int needleLen = needle.length();

    auto LPS = makeLPS(needle);

    int haystackPtr = 0;
    int needlePtr = 0;
    while (haystackPtr < haystackLen) {
        if (haystack[haystackPtr] == needle[needlePtr]) {
            ++haystackPtr;
            ++needlePtr;
            if (needlePtr == needleLen) {
                return haystackPtr - needleLen;
            }
        }
        else {
            if (needlePtr == 0) {
                // zero matched so far, only move haystack
                ++haystackPtr;
            }
            else {
                needlePtr = LPS[needlePtr - 1];
            }
        }
    }

    // no match if we reach here
    return -1;
}