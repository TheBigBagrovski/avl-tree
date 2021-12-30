#include "avl-tree.h"
#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>

Tree *createTestTree() {
    Tree *tree = newTree(NULL);
    insert(tree, 50);
    insert(tree, 40);
    insert(tree, 60);
    insert(tree, 20);
    insert(tree, 5);
    insert(tree, 15);
    insert(tree, 90);
    insert(tree, 85);
    insert(tree, 70);
    insert(tree, 75);
    insert(tree, 52);
    insert(tree, 43);
    insert(tree, 61);
    insert(tree, 29);
    insert(tree, 9);
    insert(tree, 17);
    insert(tree, 96);
    insert(tree, 86);
    insert(tree, 76);
    insert(tree, 34);
    return tree;
}

Tree *createEqualTestTree() {
    Tree *tree = newTree(NULL);
    for (int i = 0; i < 20; i++) insert(tree, 10);
    return tree;
}

bool checkBalance(Node *root) {
    bool x = true;
    if (root == NULL) return true;
    x = checkBalance(root->leftChild);
    if (!x) return false;
    x = checkBalance(root->rightChild);
    if (!x) return false;
    if (abs(getBalanceFactor(root)) > 1) return false;
    return true;
}

void testInsert() {
    Tree *tree = newTree(NULL);
    for (int i = 200; i > 0; i -= 10) insert(tree, i);
    Node *a = search(tree, 200);
    Node *b = search(tree, 100);
    assert(a->key == 200);
    assert(b->key == 100);
    assert(checkBalance(tree->root));
    deinitTree(tree);
}

void testSearch() {
    Tree *tree = createTestTree();
    Node *a = search(tree, 15);
    Node *b = search(tree, 5);
    Node *c = search(tree, 90);
    Node *d = search(tree, 200);
    assert(a->key == 15);
    assert(b->key == 5);
    assert(c->key == 90);
    assert(d == NULL);
    assert(checkBalance(tree->root));
    deinitTree(tree);
}

void testDelete() {
    Tree *tree = createTestTree();
    delete(tree, 20);
    delete(tree, 90);
    delete(tree, 75);
    delete(tree, 5);
    assert(checkBalance(tree->root));
    deinitTree(tree);
}

void testDeleteEqual() {
    Tree *tree = createEqualTestTree();
    delete(tree, 10);
    delete(tree, 10);
    delete(tree, 10);
    delete(tree, 10);
    delete(tree, 10);
    assert(checkBalance(tree->root));
    deinitTree(tree);
}

int main() {
    testInsert();
    testSearch();
    testDelete();
    testDeleteEqual();

    return 0;
}