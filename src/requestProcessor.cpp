#include "RequestProcessor.h"
#include <cmath>
#include <iostream>
#include <string>

using namespace std;

static string* splitWords(const string& text, int& count) {
    count = 0;

    // contar palavras primeiro
    bool inWord = false;
    for (char c : text) {
        if (c != ' ' && !inWord) {
            count++;
            inWord = true;
        } else if (c == ' ') {
            inWord = false;
        }
    }

    if (count == 0)
        return nullptr;

    string* parts = new string[count];

    int index = 0;
    string current = "";
    inWord = false;

    for (char c : text) {
        if (c != ' ') {
            current.push_back(c);
            inWord = true;
        } else if (inWord) {
            parts[index++] = current;
            current = "";
            inWord = false;
        }
    }

    if (inWord)
        parts[index++] = current;

    return parts;
}

RequestProcessor::RequestProcessor(StreetList* streets, WordIndex* index) {
    this->streets = streets;
    this->index = index;
}

double RequestProcessor::computeDistance(double lat1, double long1, double lat2, double long2) const {
    double dx = lat1 - lat2;
    double dy = long1 - long2;
    return sqrt(dx*dx + dy*dy);
}

double* RequestProcessor::intersect(double* a, int aSize, double* b, int bSize, int& outSize) const {
    outSize = 0;
    int max = (aSize < bSize ? aSize : bSize);
    double* result = new double[max];

    for (int i = 0; i < aSize; i++) {
        for (int j = 0; j < bSize; j++) {
            if (a[i] == b[j]) {
                result[outSize++] = a[i];
            }
        }
    }

    return result;
}

void RequestProcessor::sortCandidates(Candidate* arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j].distance < arr[minIndex].distance) {
                minIndex = j;
            }
        }
        if (minIndex != i) {
            Candidate temp = arr[i];
            arr[i] = arr[minIndex];
            arr[minIndex] = temp;
        }
    }
}

int RequestProcessor::processRequest(const Request& req, Candidate*& results) {

    int wc = 0;
    string* words = splitWords(req.getQueryName(), wc);

    if (wc == 0) {
        results = nullptr;
        delete[] words;
        return 0;
    }

    Word* w = index->search(words[0]);

    if (!w || w->getCount() == 0) {
        results = nullptr;
        delete[] words;
        return 0;
    }

    int sizeA = w->getCount();
    double* setA = new double[sizeA];

    for (int i = 0; i < sizeA; i++)
        setA[i] = w->getStreetIdAt(i);

    for (int k = 1; k < wc; k++) {
        Word* wk = index->search(words[k]);

        if (!wk || wk->getCount() == 0) {
            delete[] setA;
            delete[] words;
            results = nullptr;
            return 0;
        }

        int sizeB = wk->getCount();
        double* setB = new double[sizeB];

        for (int i = 0; i < sizeB; i++)
            setB[i] = wk->getStreetIdAt(i);

        int outSize;
        double* merged = intersect(setA, sizeA, setB, sizeB, outSize);

        delete[] setA;
        delete[] setB;

        setA = merged;
        sizeA = outSize;

        if (sizeA == 0) {
            delete[] setA;
            delete[] words;
            results = nullptr;
            return 0;
        }
    }

    delete[] words;

    results = new Candidate[sizeA];
    int count = 0;

    for (int i = 0; i < sizeA; i++) {
        double id = setA[i];

        for (int j = 0; j < streets->getSize(); j++) {
            Street s = streets->getAt(j);

            if (s.getIdLog() == id) {
                results[count].idLog = id;
                results[count].name = s.getStreetName();
                results[count].distance = computeDistance(
                    req.getLatOrigin(), req.getLongOrigin(),
                    s.getAvgLatitude(), s.getAvgLongitude()
                );
                count++;
                break;
            }
        }
    }

    delete[] setA;
    return count;
}

void RequestProcessor::processAll(Request* requests, int count, int maxAnswers) {

    cout << count << "\n";

    for (int i = 0; i < count; i++) {

        Candidate* results = nullptr;
        int total = processRequest(requests[i], results);

        int R = (total < maxAnswers ? total : maxAnswers);

        cout << requests[i].getIdRequest() << ";" << R << "\n";

        if (R > 0) {

            sortCandidates(results, total);

            for (int j = 0; j < R; j++) {
                cout << (int)results[j].idLog << ";" 
                          << results[j].name << "\n";
            }
        }

        delete[] results;
    }
}
