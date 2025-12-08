#include "WordIndex.h"
#include <iostream>


WordIndex::WordIndex() {
    root = nullptr;
}

WordIndex::~WordIndex() {
    freeTree(root);
}

void WordIndex::freeTree(Node* node) {
    if (!node) return;
    freeTree(node->left);
    freeTree(node->right);
    delete node;
}


int WordIndex::height(Node* n) const {
    return n ? n->height : 0;
}

int WordIndex::balanceFactor(Node* n) const {
    return n ? height(n->left) - height(n->right) : 0;
}

WordIndex::Node* WordIndex::rotateRight(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = std::max(height(y->left), height(y->right)) + 1;
    x->height = std::max(height(x->left), height(x->right)) + 1;

    return x;
}

WordIndex::Node* WordIndex::rotateLeft(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = std::max(height(x->left), height(x->right)) + 1;
    y->height = std::max(height(y->left), height(y->right)) + 1;

    return y;
}

WordIndex::Node* WordIndex::insert(Node* node, const std::string& word, double idLog) {
    if (!node) {
        Word w(word);
        w.addStreetId(idLog);
        return new Node(w);
    }

    if (word < node->data.getText()) {
        node->left = insert(node->left, word, idLog);
    } else if (word > node->data.getText()) {
        node->right = insert(node->right, word, idLog);
    } else {
        node->data.addStreetId(idLog);
        return node;
    }

    node->height = 1 + std::max(height(node->left), height(node->right));

    int bf = balanceFactor(node);

    if (bf > 1 && word < node->left->data.getText())
        return rotateRight(node);

    if (bf < -1 && word > node->right->data.getText())
        return rotateLeft(node);

    if (bf > 1 && word > node->left->data.getText()) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    if (bf < -1 && word < node->right->data.getText()) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}


void WordIndex::addWordOccurrence(const std::string& word, double idLog) {
    root = insert(root, word, idLog);
}


WordIndex::Node* WordIndex::find(Node* node, const std::string& word) const {
    if (!node) return nullptr;
    if (word == node->data.getText()) return node;
    if (word < node->data.getText()) return find(node->left, word);
    return find(node->right, word);
}

Word* WordIndex::search(const std::string& word) {
    Node* n = find(root, word);
    return n ? &n->data : nullptr;
}


void WordIndex::printInOrder() const {
    printInOrder(root);
}

void WordIndex::printInOrder(Node* node) const {
    if (!node) return;

    printInOrder(node->left);
    std::cout << node->data.getText() << " -> ";

    for (int i = 0; i < node->data.getCount(); i++)
        std::cout << node->data.getStreetIdAt(i) << " ";

    std::cout << "\n";

    printInOrder(node->right);
}
