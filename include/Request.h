#ifndef REQUEST_H
#define REQUEST_H

class Request {
private:
    int requestId;               // Identifier of the query request
    char* rawQueryText;          // Full query text (e.g. "CALDEIRA BRANT")

    char** words;                // Array of extracted words
    int wordCount;
    int wordCapacity;

    double originLatitude;       // Origin point for distance calculation
    double originLongitude;

    char* copyString(const char* s);
    void ensureWordCapacity();
    void extractWords();         // Parse rawQueryText into words[]

public:
    // Constructor
    Request(
        int requestId,
        const char* queryText,
        double originLatitude,
        double originLongitude
    );

    // Destructor
    ~Request();

    // Getters
    int getRequestId() const;
    const char* getRawQueryText() const;
    int getWordCount() const;
    const char* getWordAt(int index) const;
    double getOriginLatitude() const;
    double getOriginLongitude() const;

    // Setters
    void setRequestId(int value);
    void setOriginLatitude(double value);
    void setOriginLongitude(double value);

    // Replace the entire query text (re-parses words)
    void setQueryText(const char* newText);
};

#endif
