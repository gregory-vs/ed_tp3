#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <string>

class Tokenizer {
public:
    static std::string* split(const std::string& text, int& wordCount);
};

#endif
