#include <iostream>
#include <cstdlib>
#include <ctime>
#include "BinaryTree.hpp"


void BinaryTree::Preorder(Node* curNode, Container& container){
    if(curNode == nullptr){
        return;
    }
    container.arr[container.count++] = curNode->number;
    Preorder(curNode->left, container);
    Preorder(curNode->right, container);
}

void BinaryTree::RotationCounterClockwise(Node* node){
    Node* parent = node->parent;
    if(node->left){
        parent->right = node->left;
        node->left->parent = parent;
    }
    else
        parent->right = nullptr;

    node->left = parent;
    if(parent->parent)
        node->parent = parent->parent;
    else{
        node->parent = nullptr;
        _root = node;
    }

    parent->parent = node;

}

void BinaryTree::RotationClockwise(Node* node){
    Node* parent = node->parent;
    if(node->right){
        parent->left = node->right;
        node->right->parent = parent;
    }
    else
        parent->left = nullptr;

    node->right = parent;
    if(parent->parent)
        node->parent = parent->parent;
    else{
        node->parent = nullptr;
        _root = node;
    }
    parent->parent = node;
}

void BinaryTree::RebalanceLeftTree(Node* node){
    if(node->balancefactor == -1){
        RotationClockwise(node);
        node->balancefactor = 0;
        node->right->balancefactor = 0;
    }
    else if(node->balancefactor == 1){
        Node* startNode = node->right;
        RotationCounterClockwise(startNode);
        RotationClockwise(startNode);
        if(startNode->balancefactor == 1){
            startNode->left->balancefactor = -1;
            startNode->right->balancefactor = 0;
        }
        else if (startNode->balancefactor == -1){
            startNode->left->balancefactor = 0;
            startNode->right->balancefactor = 1;
        }
        else if(startNode->balancefactor == 0){
            startNode->left->balancefactor = 0;
            startNode->right->balancefactor = 0;
        }

        startNode->balancefactor = 0;
    }
    else
        throw std::exception("rebalance gone wrong");

}

void BinaryTree::RebalanceRightTree(Node* node){
    if(node->balancefactor == 1){
        RotationCounterClockwise(node);
        node->balancefactor = 0;
        node->left->balancefactor = 0;
    }
    else if (node->balancefactor == -1){
        Node* startNode = node->left;
        RotationClockwise(startNode);
        RotationCounterClockwise(startNode);

        if(startNode->balancefactor == 1){
            startNode->left->balancefactor = -1;
            startNode->right->balancefactor = 0;
        }
        else if (startNode->balancefactor == -1){
            startNode->left->balancefactor = 0;
            startNode->right->balancefactor = 1;
        }
        else if(startNode->balancefactor == 0){
            startNode->left->balancefactor = 0;
            startNode->right->balancefactor = 0;
        }

        startNode->balancefactor = 0;
    }
    else
        throw std::exception("rebalance gone wrong");
}


void BinaryTree::UpdateBalanceFactor(Node* insertedNode){
    Node* node = insertedNode;
    Node* parent = insertedNode->parent;
    if(!parent)
        return;
    if(parent->left == node)
        parent->balancefactor--;
    else 
        parent->balancefactor++;

    while(parent->parent && parent->balancefactor < 2 && parent->balancefactor > -2){
        node = parent;
        parent = node->parent;
        if (node->balancefactor == 0)
            return;
        if(parent->left == node)
            parent->balancefactor--;
        else 
            parent->balancefactor++;
    }
    if(parent->balancefactor >= 2)
        RebalanceRightTree(node);
    else if (parent->balancefactor <=-2)
        RebalanceLeftTree(node); 
}


bool BinaryTree::Insert(int num){
    if(!_root){
        _root = new Node{num};
        return true;
    }
    return Insert(_root, num);
}

bool BinaryTree::Insert(Node* curNode, int num){
    if(num == curNode->number)
        return true;
    else if(num > curNode->number){
        if(!curNode->right){
            Node* newNode = new Node{num};
            newNode->parent = curNode;
            curNode->right = newNode;
            if(!_allowUnbalancedTree)
                UpdateBalanceFactor(newNode);
            return true;
        }
        return Insert(curNode->right, num);
    }
    else if(num < curNode->number){ 
        if(!curNode->left){
            Node* newNode = new Node{num};
            newNode->parent = curNode;
            curNode->left = newNode;
            if(!_allowUnbalancedTree)
                UpdateBalanceFactor(newNode);
            return true;
        }
        return Insert(curNode->left, num);
    }
    return false;
}

bool BinaryTree::InsertArr(int arr[], int count){
    if (!count)
        return false;
    _root = new Node{arr[0]};
    for(int i = 1; i < count; i++){
        Insert(_root, arr[i]);
    }
    return true;
}

void BinaryTree::PrintContainer(Container& container){
    printf("[");
    for(int i = 0; i<container.count; i++){
        printf("%d,", container.arr[i]);
    }
    printf("]");
}

int* BinaryTree::createRandomArr(const int count){
    srand(time(0)); // for generating different sequence of random numbers
    int* arr = new int[count];
    for(int i = 0; i < count; ++i){
        arr[i] = rand() % 100; // generates a random number between 0 and 99
    }
    return arr;
}

Node* BinaryTree::Find(int num){
    return Find(_root, num);
}

Node* BinaryTree::Find(Node* node, int num){
    if(!node)
        return 0;
    else if (node->number == num)
        return node;
    else if (num > node->number)
        return Find(node->right, num);
    else 
        return Find(node->left, num);
}

void BinaryTree::DeleteLeftSubTree(Node* node, Node* root){
    if(node->right){
        DeleteLeftSubTree(node->right, root);
        return;
    }
    root->number = node->number;
    if(node->left){
        node->left->parent = node->parent;
        node->parent->right = node->left;
    }
    else{
        node->parent->right = nullptr;
    }
    delete node;
}

void BinaryTree::DeleteRightSubTree(Node* node, Node* root){
    if(node->left){
        DeleteRightSubTree(node->left, root);
        return;
    }
    root->number = node->number;
    if(node->right){
        node->right->parent = node->parent;
        node->parent->left = node->right;
    }
    else{
        node->parent->left = nullptr;
    }
    delete node;
}

bool BinaryTree::Delete(int num){
    return Delete(_root, num);
}

bool BinaryTree::Delete(Node* root, int num){
    Node* delNode = Find(root, num);
    if(!delNode)
        return false;
    else if(!delNode->left && !delNode->right){
        if(delNode->parent->left == delNode)
            delNode->parent->left = nullptr;
        else
            delNode->parent->right = nullptr;
        delete delNode;
        return true;
    }
    else if(delNode->left && delNode->right){
        int chooseSubTree = num%2;
        if(chooseSubTree)
            DeleteRightSubTree(delNode->right, delNode);
        else
            DeleteLeftSubTree(delNode->left, delNode);
        return true;
    }
    else if(delNode->left || delNode->right){
        Node* childNode = delNode->left ? delNode->left: delNode->right;
        if(delNode->parent->left == delNode) 
            delNode->parent->left = childNode;
        else 
            delNode->parent->right = childNode;
        childNode->parent = delNode->parent;
        delete delNode;
        return true;
    }
    return false;

}


