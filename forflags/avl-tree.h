#pragma once

#include <stdio.h>
#include <stdlib.h>
// defines node struct and type
typedef struct node_str { // define node struct and type
    int key;
    struct node_str *leftChild;
    struct node_str *rightChild;
    unsigned char height;
} Node;

// defines tree struct and type
typedef struct tree_str {
    Node *root;
} Tree;

Node *newNode(int key);
Tree *newTree(Node *root);
int getHeight(Node *N);
int getBalanceFactor(Node *node);
Node *search(Tree *tree, int inputKey);
Node *rotateRight(Node *y);
Node *rotateLeft(Node *x);
Node* balance(Node* root);
Node *insertInner(Node *root, int inputKey);
void insert(Tree *tree, int inputKey);
Node *minValueNode(Node *node);
Node *deleteInner(Node *root, int inputKey);
void delete(Tree *tree, int inputKey);
void printTreeInner(Node *root, int height);
void printTree(Tree *tree);
void printTreeInFileInner(Node *root, int height, FILE *file);
void printTreeInFile(Tree *tree, FILE *file);
void deinitNode(Node *node);
void deinitTreeInner(Node *root);
void deinitTree(Tree *tree);