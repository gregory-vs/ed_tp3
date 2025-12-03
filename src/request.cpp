#include "Request.h"
#include <cstring>
#include <cstdlib>

// Copy string helper
char* Request::copyString(const char* s) {
    char* c = (char*) malloc((strlen(s) + 1) * sizeof(char));
    strcpy(c, s);
    return c;
}

// Ensure capacity for the words array
void Request::ensureWordCapacity() {
    if (wordCount < wordCapacity) return;

    int newCapacity = (wordCapacity == 0) ? 4 : wordCapacity * 2;
    char** newArray = (char**) malloc(newCapacity * sizeof(char*));

    for (int i = 0; i < wordCount; i++)
        newArray[i] = words[i];

    free(words);
    words = newArray;
    wordCapacity = newCapacity;
}

// Extract words from rawQueryText into words[]
void Request::extractWords() {
    wordCount = 0;

    const int len = strlen(rawQueryText);
    char* buffer = (char*) malloc((len + 1) * sizeof(char));
    strcpy(buffer, rawQueryText);

    char* token = strtok(buffer, " ");
    while (token != NULL) {
        ensureWordCapacity();
        words[wordCount] = copyString(token);
        wordCount++;

        token = strtok(NULL, " ");
    }

    free(buffer);
}

// Constructor
Request::Request(
    int requestId,
    const char* queryText,
    double originLatitude,
    double originLongitude
) {
    this->requestId = requestId;
    this->rawQueryText = copyString(queryText);
    this->originLatitude = originLatitude;
    this->originLongitude = originLongitude;

    this->words = NULL;
    this->wordCount = 0;
    this->wordCapacity = 0;

    extractWords();
}

// Destructor
Request::~Request() {
    free(rawQueryText);

    for (int i = 0; i < wordCount; i++)
        free(words[i]);

    free(words);
}

// Getters
int Request::getRequestId() const { return requestId; }
const char* Request::getRawQueryText() const { return rawQueryText; }
int Request::getWordCount() const { return wordCount; }
const char* Request::getWordAt(int index) const { return words[index]; }
double Request::getOriginLatitude() const { return originLatitude; }
double Request::getOriginLongitude() const { return originLongitude; }

// Setters
void Request::setRequestId(int value) { requestId = value; }
void Request::setOriginLatitude(double value) { originLatitude = value; }
void Request::setOriginLongitude(double value) { originLongitude = value; }

// Replace query text (also re-extracts words)
void Request::setQueryText(const char* newText) {
    free(rawQueryText);
    rawQueryText = copyString(newText);

    // Free old words
    for (int i = 0; i < wordCount; i++)
        free(words[i]);

    wordCount = 0;

    extractWords();
}
