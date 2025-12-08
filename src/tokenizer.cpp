#include "Tokenizer.h"
#include <string>

std::string* Tokenizer::split(const std::string& text, int& wordCount) {
    wordCount = 0;

    bool inWord = false;
    for (char c : text) {
        if (c != ' ' && !inWord) {
            inWord = true;
            wordCount++;
        } else if (c == ' ') {
            inWord = false;
        }
    }

    std::string* words = new std::string[wordCount];

    int index = 0;
    std::string current = "";
    inWord = false;

    for (char c : text) {
        if (c != ' ') {
            current += c;
            inWord = true;
        } else if (inWord) {
            words[index++] = current;
            current = "";
            inWord = false;
        }
    }

    if (inWord) {
        words[index] = current;
    }

    return words;
}
