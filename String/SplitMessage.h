#pragma once
#include "..\Common.h"

// https://leetcode.com/problems/split-message-based-on-limit/
int numberLen(int num) {
    return to_string(num).length();
}

vector<string> splitMessage(string message, int limit) {
    // given parts, we can check whether we can split the message this way
    // we want the least parts, so go from parts = 1 and increment, find the first parts that is viable

    // for parts, calculate the total char counts:
    // <1/parts>string_1, <2/parts>string_2, ... <parts/parts>string_parts
    // we just need to check how many extra chars from the <1/parts>, <2/parts>, ..
    // </>: 3 chars for each part
    // numberLen(parts): for each part
    // 1, 2, ..: accumulate as we increment parts

    int len = message.length();
    int parts = 1;
    int indexLenTotal = 1;
    while (len + indexLenTotal + 3 * parts + parts * numberLen(parts) > limit * parts) { // too many chars to split into parts messages
        // when can we not split the message in any way?
        // we need to have <parts/parts> as the last element, if that part cannot include any real char, we cannot split the message
        // if we increment parts, then <parts/parts> gets longer, we still cannot fit any real char
        if (2 * numberLen(parts) + 3 >= limit) {
            return {};
        }

        ++parts;
        indexLenTotal += numberLen(parts);
    }

    vector<string> result{};
    // now we have the smallest parts value
    int wordIndex = 1;
    int strIndex = 0;
    while (strIndex < len) {
        string right = "<" + to_string(wordIndex++) + "/" + to_string(parts) + ">";
        int remainLen = limit - right.length();
        string left;
        for (int i = 0; i < remainLen && strIndex < len; ++i) {
            left += message[strIndex++];
        }

        left += right;
        result.push_back(left);
    }
    return result;
}
