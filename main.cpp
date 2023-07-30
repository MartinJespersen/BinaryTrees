#include <iostream>
#include "src/BinaryTree.hpp"
int main(){
    BinaryTree tree;
    Container container = {};
    int count = 10;
    int* arr = tree.createRandomArr(count);
    tree.InsertArr(arr, count);
    tree.Preorder(tree._root, container);
    tree.PrintContainer(container);
}