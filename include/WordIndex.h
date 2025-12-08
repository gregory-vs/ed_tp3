#ifndef WORDINDEX_H
#define WORDINDEX_H

#include "Word.h"
#include <string>

class WordIndex {

private:
    struct Node {
        Word data;
        Node* left;
        Node* right;
        int height;

        Node(const Word& w)
            : data(w), left(nullptr), right(nullptr), height(1) {}
    };

    Node* root;

    int height(Node* n) const;
    int balanceFactor(Node* n) const;

    Node* rotateRight(Node* y);
    Node* rotateLeft(Node* x);

    Node* insert(Node* node, const std::string& word, double idLog);
    Node* find(Node* node, const std::string& word) const;

    Node* insertWordOnly(Node* node, const std::string& word);
    Node* findNode(Node* node, const std::string& word) const;

public:
    WordIndex();
    ~WordIndex();

    void addWordOccurrence(const std::string& word, double idLog);

    Word* search(const std::string& word);

    void printInOrder() const;
    void printInOrder(Node* node) const;

    void freeTree(Node* node);
};

#endif
