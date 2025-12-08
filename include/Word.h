#ifndef WORD_H
#define WORD_H

#include <string>

class Word {
private:
    std::string text;
    double* streetIds;
    int count;
    int capacity;

    void expand();

public:
    Word();
    Word(const std::string& text);
    Word(const Word& other);
    Word& operator=(const Word& other);

    ~Word();

    std::string getText() const;
    int getCount() const;
    double getStreetIdAt(int index) const;

    void setText(const std::string& value);

    void addStreetId(double idLog);

    void print() const;
};

#endif
