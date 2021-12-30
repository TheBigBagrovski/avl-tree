#pragma once

#include <stdbool.h>

Tree *createTestTree();
Tree *createEqualTestTree();
bool checkBalance(Node *root);
void testInsert();
void testSearch();
void testDelete();
void testDeleteEqual();