#include <iostream>
#include <cstdlib>
#include <fstream>
#include "Address.h"
#include "InputLoader.h"
#include "AddressList.h"
#include "StreetList.h"
#include "WordIndex.h"
#include "Request.h"
#include "RequestProcessor.h"

using namespace std;

static string* splitWords(const std::string& text, int& count) {
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

    std::string* parts = new std::string[count];

    int index = 0;
    std::string current = "";
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

int main() {

    int addressCount = 0, numRequests = 0, maxAnswers = 0;

    cin >> addressCount;
    cin.ignore();

    Address* list = InputLoader::loadFromCin(addressCount);

    cin >> numRequests >> maxAnswers;
    cin.ignore();

    Request* requests = InputLoader::loadRequestsFromCin(numRequests);

    AddressList addressList(list, addressCount);

    StreetList streetList;
    streetList.buildFromAddressList(addressList);

    WordIndex wordIndex;

    for (int i = 0; i < streetList.getSize(); i++) {
        Street s = streetList.getAt(i);

        int wc = 0;
        string* words = splitWords(s.getFullName(), wc);

        for (int j = 0; j < wc; j++) {
            wordIndex.addWordOccurrence(words[j], s.getIdLog());
        }

        delete[] words;
    }

    RequestProcessor processor(&streetList, &wordIndex);
    processor.processAll(requests, numRequests, maxAnswers);

    delete[] list;
    delete[] requests;

    return 0;
}
