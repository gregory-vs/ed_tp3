#include <iostream>
#include <cstdlib>
#include <fstream>
#include "Address.h"
#include "InputLoader.h"
#include "AddressList.h"
#include "StreetList.h"
#include "WordIndex.h"
#include "Tokenizer.h"
#include "Request.h"
#include "RequestProcessor.h"

using namespace std;

int main() {

    ifstream file("entrada.txt");

    int addressCount = 0, numRequests = 0, maxAnswers = 0;
    cin.rdbuf(file.rdbuf());

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
        string* words = Tokenizer::split(s.getFullName(), wc);

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
