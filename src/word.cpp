#include "Word.h"
#include <cstring>
#include <cstdlib>

// Helper: copy C-string into newly allocated memory
char* Word::copyString(const char* s) {
    char* c = (char*) malloc((strlen(s) + 1) * sizeof(char));
    strcpy(c, s);
    return c;
}

// Ensure capacity for at least one more streetId
void Word::ensureCapacity() {
    if (streetCount < streetCapacity) {
        return;
    }

    int newCapacity = (streetCapacity == 0) ? 4 : streetCapacity * 2;
    int* newArray = (int*) malloc(newCapacity * sizeof(int));

    for (int i = 0; i < streetCount; i++) {
        newArray[i] = streetIds[i];
    }

    free(streetIds);
    streetIds = newArray;
    streetCapacity = newCapacity;
}

// Check if a streetId is already stored (to avoid duplicates)
bool Word::containsStreetId(int streetId) const {
    for (int i = 0; i < streetCount; i++) {
        if (streetIds[i] == streetId) {
            return true;
        }
    }
    return false;
}

// Constructor
Word::Word(const char* text) {
    this->text = copyString(text);
    this->streetIds = NULL;
    this->streetCount = 0;
    this->streetCapacity = 0;
}

// Destructor
Word::~Word() {
    free(text);
    free(streetIds);
}

// Getters
const char* Word::getText() const {
    return text;
}

int Word::getStreetCount() const {
    return streetCount;
}

const int* Word::getStreetIds() const {
    return streetIds;
}

int Word::getStreetIdAt(int index) const {
    // Assumes index is valid (0 <= index < streetCount)
    return streetIds[index];
}

// Add a streetId to the list if not already present
void Word::addStreetId(int streetId) {
    if (containsStreetId(streetId)) {
        return; // avoid duplicates
    }

    ensureCapacity();
    streetIds[streetCount] = streetId;
    streetCount++;
}
