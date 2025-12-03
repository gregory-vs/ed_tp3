#ifndef WORD_H
#define WORD_H

class Word {
private:
    char* text;        // The word itself (e.g. "CALDEIRA", "BRANT")
    int* streetIds;    // Dynamic array of street IDs where this word occurs
    int streetCount;   // Current number of street IDs
    int streetCapacity;// Allocated capacity for streetIds

    char* copyString(const char* s);
    void ensureCapacity();
    bool containsStreetId(int streetId) const;

public:
    // Constructor: creates a word with no associated streets yet
    Word(const char* text);

    // Destructor
    ~Word();

    // Getters
    const char* getText() const;
    int getStreetCount() const;
    const int* getStreetIds() const;  // pointer to internal array (read-only)
    int getStreetIdAt(int index) const;

    // Add a streetId to the list (ignores duplicates)
    void addStreetId(int streetId);
};

#endif
