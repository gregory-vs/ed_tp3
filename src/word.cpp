#include "Word.h"
#include <iostream>

Word::Word()
    : text(""), count(0), capacity(2)
{
    streetIds = new double[capacity];
}

Word::Word(const std::string& text)
    : text(text), count(0), capacity(2)
{
    streetIds = new double[capacity];
}

Word::Word(const Word& other)
    : text(other.text),
      count(other.count),
      capacity(other.capacity)
{
    streetIds = new double[capacity];
    for (int i = 0; i < count; ++i) {
        streetIds[i] = other.streetIds[i];
    }
}

Word& Word::operator=(const Word& other) {
    if (this != &other) {
        // libera o array atual
        delete[] streetIds;

        text = other.text;
        count = other.count;
        capacity = other.capacity;

        streetIds = new double[capacity];
        for (int i = 0; i < count; ++i) {
            streetIds[i] = other.streetIds[i];
        }
    }
    return *this;
}

Word::~Word() {
    delete[] streetIds;
}

std::string Word::getText() const {
    return text;
}

int Word::getCount() const {
    return count;
}

double Word::getStreetIdAt(int index) const {
    if (index < 0 || index >= count) return -1;
    return streetIds[index];
}

void Word::setText(const std::string& value) {
    text = value;
}


void Word::expand() {
    capacity *= 2;
    double* newArr = new double[capacity];

    for (int i = 0; i < count; i++) {
        newArr[i] = streetIds[i];
    }

    delete[] streetIds;
    streetIds = newArr;
}


void Word::addStreetId(double idLog) {
    if (count == capacity) {
        expand();
    }

    streetIds[count] = idLog;
    count++;
}


void Word::print() const {
    std::cout << "Word: " << text << "\nOccurs in logradouros: ";

    for (int i = 0; i < count; i++) {
        std::cout << streetIds[i];
        if (i < count - 1) std::cout << ", ";
    }

    std::cout << "\n";
}
