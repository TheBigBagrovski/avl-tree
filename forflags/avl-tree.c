#include <stdio.h>
#include <stdlib.h>
#include "avl-tree.h"

//constructs a node with the given key and returns its pointer
Node *newNode(int key) {
    Node *node = (Node *) malloc(sizeof(Node)); //allocates memory for our node
    node->key = key;
    node->leftChild = NULL;
    node->rightChild = NULL;
    node->height = 1;  // default height is 1
    return node;
}

//constructs a tree with the given root (some node pointer), returns tree's pointer
Tree *newTree() {
    Tree *tree = (Tree *) malloc(sizeof(Tree));    //allocates memory for tree
    tree->root = NULL;
    return tree;
}

// get the height of the tree (height of the highest subtree)
int getHeight(Node *N) {
    if (N == NULL) return 0;
    return N->height;
}

/* gets balance factor of input node
-2 => right subtree is too high
-1, 0, 1 => balanced
 2 => left subtree is too high*/
int getBalanceFactor(Node *node) {
    if (node == NULL) return 0;
    return getHeight(node->leftChild) - getHeight(node->rightChild);
}

Node *search(Tree *tree, int inputKey) {
    Node *currentNode = tree->root;
    while (currentNode->key != inputKey) {
        if (inputKey < currentNode->key) currentNode = currentNode->leftChild;
        else currentNode = currentNode->rightChild;
        if (currentNode == NULL) return NULL;
    }
    return currentNode;
}

// right rotation
Node *rotateRight(Node *y) {
    Node *x = y->leftChild;
    Node *B = x->rightChild;
    // rotation
    x->rightChild = y;
    y->leftChild = B;
    // updating heights
    y->height = max(getHeight(y->leftChild), getHeight(y->rightChild)) + 1;
    x->height = max(getHeight(x->leftChild), getHeight(x->rightChild)) + 1;
    // return new root
    return x;
}

// left rotation
Node *rotateLeft(Node *x) {
    Node *y = x->rightChild;
    Node *B = y->leftChild;
    // rotation
    y->leftChild = x;
    x->rightChild = B;
    // updating heights
    x->height = max(getHeight(x->leftChild), getHeight(x->rightChild)) + 1;
    y->height = max(getHeight(y->leftChild), getHeight(y->rightChild)) + 1;
    // return new root
    return y;
}

Node *balance(Node *root) {
    int bf = getBalanceFactor(root);
    // LL case
    if (bf > 1 && getBalanceFactor(root->leftChild) >= 0)
        return rotateRight(root);
    // LR case
    if (bf > 1 && getBalanceFactor(root->leftChild) < 0) {
        root->leftChild = rotateLeft(root->leftChild);
        return rotateRight(root);
    }
    // RR case
    if (bf < -1 && getBalanceFactor(root->rightChild) <= 0)
        return rotateLeft(root);
    // RL case
    if (bf < -1 && getBalanceFactor(root->rightChild) > 0) {
        root->rightChild = rotateRight(root->rightChild);
        return rotateLeft(root);
    }
    return root;
}

// recursive function to insert a node with the given key in the tree with given root, returns the new root of the subtree.
Node *insertInner(Node *root, int inputKey) {
    if (root == NULL) return (newNode(inputKey));
    else {
        if (inputKey < root->key) root->leftChild = insertInner(root->leftChild, inputKey);
        else root->rightChild = insertInner(root->rightChild, inputKey);
        // update height
        root->height = 1 + max(getHeight(root->leftChild), getHeight(root->rightChild));
        // return the root, continue getting back in recursion
        return balance(root);
    }
}

// wrapper fot insertInner (using tree)
void insert(Tree *tree, int inputKey) {
    tree->root = insertInner(tree->root, inputKey);    //new root for tree if changed
}

Node *minValueNode(Node *node) {
    Node *current = node;
    // loop down to find the leftmost leaf
    while (current->leftChild != NULL) current = current->leftChild;
    return current;
}

// Recursive function to delete a node with given inputKey
// from subtree with given root. It returns root of
// the modified subtree.
Node *deleteInner(Node *root, int inputKey) {
    if (root == NULL) return root;
    // if inputKey < key our node if in the left subtree
    if (inputKey < root->key) root->leftChild = deleteInner(root->leftChild, inputKey);
    else if (inputKey > root->key) root->rightChild = deleteInner(root->rightChild, inputKey);
    else { // if inputKey == key we found node to be deleted
        if ((root->leftChild == NULL) && (root->rightChild == NULL)) { // no children
            root = NULL;
            deinitNode(root);
        } else if ((root->leftChild == NULL) || (root->rightChild == NULL)) { // one child
            Node *helper = root->leftChild ? root->leftChild : root->rightChild;
            *root = *helper;
            deinitNode(helper);
        } else { // two children
            Node *helper = minValueNode(root->rightChild); // leftmost leaf (heir)
            root->key = helper->key; // node to delete becomes heir
            root->rightChild = deleteInner(root->rightChild, helper->key); // deleting leftmost leaf with rebalancing
        }
    }
    if (root == NULL) return root;
    root->height = max(getHeight(root->leftChild), getHeight(root->rightChild)) + 1;
    return balance(root);
}

void delete(Tree *tree, int inputKey) {
    tree->root = deleteInner(tree->root, inputKey);     //new root for tree if changed
}

void printTreeInner(Node *root, int height) {
    if (root != NULL) {
        printTreeInner(root->leftChild, height + 1); // left subtree first
        for (int i = 0; i < height; i++) printf("   "); //more height - more spaces
        printf("%d\n", root->key);
        printTreeInner(root->rightChild, height + 1);
    }
}

void printTree(Tree *tree) {
    printTreeInner(tree->root, 0);
}

void printTreeInFileInner(Node *root, int height, FILE *file) {
    if (root != NULL) {
        printTreeInFileInner(root->leftChild, height + 1, file); // left subtree first
        for (int i = 0; i < height; i++) fprintf(file, "   "); //more height - more spaces
        fprintf(file, "%d\n", root->key);
        printTreeInFileInner(root->rightChild, height + 1, file);
    }
}

void printTreeInFile(Tree *tree, FILE *file) {
    printTreeInFileInner(tree->root, 0, file);
}

void deinitNode(Node *node) {
    free(node);
}

void deinitTreeInner(Node *root) {
    if (root == NULL) return;
    deinitTreeInner(root->leftChild);
    deinitTreeInner(root->rightChild);
    deinitNode(root);
}

void deinitTree(Tree *tree) {
    deinitTreeInner(tree->root);
    free(tree);
}