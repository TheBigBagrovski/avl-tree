#include "avl-tree.h"

/*
 * Данная демонстрационная программа считывает аргументы командной строки с названиями входного и
 * выходного файлов, считывает построчно числа из файла с заданным именем, создает AVL дерево, в которое
 * вставляет числа с введенными узлами и выводит полученное дерево в указанный выходной файл
*/
int main() {
//    if (argc != 2) {
//        printf("\nWrong command\n");
//        return -1;
//    }
    FILE *inputFile = fopen("input.txt", "r");
//    if (inputFile == NULL) {
//        printf("Error while reading file");
//        return -1;
//    }
    Tree *tree = newTree(NULL);
    int num;
    while (!feof(inputFile)) {
        fscanf(inputFile, "%d\n", &num);
        insert(tree, num);
    }
    fclose(inputFile);
    FILE *outputFile = fopen("output.txt", "w");
    printTreeInFile(tree, outputFile);
    fclose(outputFile);
    deinitTree(tree);
    return 0;
}