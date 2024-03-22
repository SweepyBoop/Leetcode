#pragma once
#include "..\Common.h"

// https://leetcode.com/problems/text-justification/description/?envType=study-plan-v2&envId=top-interview-150
vector<string> fullJustify(vector<string>& words, int maxWidth) {
    // need to check how many words can fit into current row, and whether this is the last line
    // <word> <word> <word>, assume one space between every two words => max words to fit into current line
    // if the last word fits into current row, then we are at the last line
    vector<string> lines;

    int n = words.size();
    int startIdx = 0; // index of the first word for current line, when we're done checking all words, startIdx == n
    while (startIdx < n) {
        int lineWidth = words[startIdx].length();
        int endIdx = startIdx;
        while (endIdx + 1 < n && lineWidth + words[endIdx + 1].length() + 1 <= maxWidth) {
            lineWidth += words[endIdx + 1].length() + 1;
            ++endIdx;
        }

        // now type [startIdx..endIdx] on current line
        string line = words[startIdx];
        // is it final line?
        if (endIdx == n - 1) {
            // no extra spaces between words
            for (int i = startIdx + 1; i <= endIdx; ++i) {
                line += ' ';
                line += words[i];
            }
            // add trailing spaces to fill the line
            int trailingSpaces = maxWidth - line.length();
            for (int i = 0; i < trailingSpaces; ++i) {
                line += ' ';
            }
        }
        else {
            if (endIdx == startIdx) {
                // only one word in current line, just add trailing spaces
                for (int i = 0; i < maxWidth - lineWidth; ++i) {
                    line += ' ';
                }
            }
            else {
                int extraSpaces = maxWidth - lineWidth;
                int gaps = endIdx - startIdx;
                int spaces = extraSpaces / gaps;
                int mod = extraSpaces % gaps; // if this is 2, then first 2 gaps have one extra space
                for (int i = startIdx + 1; i <= endIdx; ++i) {
                    line += ' ';
                    for (int j = 0; j < spaces; ++j) {
                        line += ' ';
                    }
                    if (i - startIdx <= mod) {
                        line += ' ';
                    }

                    line += words[i];
                }

            }
        }

        lines.push_back(line);
        startIdx = endIdx + 1; // if endIdx is the last word, startIdx <- n, the outer loop will terminate as expected.
    }

    return lines;
}

// https://leetcode.com/problems/rearrange-spaces-between-words/
string reorderSpaces(string text) {
    vector<string> words;
    int spaceCount = 0;
    string currentWord;
    for (char ch : text) {
        if (ch == ' ') {
            if (!currentWord.empty()) {
                words.push_back(currentWord);
            }
            currentWord = {};
            ++spaceCount;
        }
        else {
            currentWord += ch;
        }
    }
    if (!currentWord.empty()) {
        words.push_back(currentWord);
    }

    string ans = words[0];
    int n = words.size();
    if (n == 1) {
        // only have one word, append all the spaces to the end
        for (int i = 0; i < text.length() - words[0].length(); ++i) {
            ans += ' ';
        }
    }
    else {
        int gaps = n - 1;
        int spaces = spaceCount / gaps;
        int trailing = spaceCount % gaps;

        for (int i = 1; i < words.size(); ++i) {
            for (int j = 0; j < spaces; ++j) {
                ans += ' ';
            }
            ans += words[i];
        }

        for (int i = 0; i < trailing; ++i) {
            ans += ' ';
        }
    }

    return ans;
}
