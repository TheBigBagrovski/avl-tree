#include <stdio.h>
#include "avl-tree.h"

/*
 * Данная демонстрационная программа считывает аргументы командной строки с названиями входного и
 * выходного файлов, считывает построчно числа из файла с заданным именем, создает AVL дерево, в которое
 * вставляет числа с введенными узлами и выводит полученное дерево в указанный выходной файл
*/
int main(int argc, char *argv[]) {
//    if (argc != 2) {
//        printf("\nWrong command\n");
//        return -1;
//    }
    FILE *inputFile = fopen(argv[1], "r");
    if (inputFile == NULL) {
        printf("Error while reading file");
        return -1;
    }
    Tree *tree = newTree();
    int num;
    while (!feof(inputFile)) {
        fscanf(inputFile, "%d\n", &num);
        insert(tree, num);
    }
    fclose(inputFile);
    FILE *outputFile = fopen(argv[2], "w");
    printTreeInFile(tree, outputFile);
    fclose(outputFile);
    deinitTree(tree);
    return 0;
}