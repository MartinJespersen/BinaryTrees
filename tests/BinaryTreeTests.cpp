#include <gtest/gtest.h>
#include "../src/BinaryTree.hpp"
namespace{
TEST(TestCase1, FindTrue){
    BinaryTree tree;
    const int count = 5;
    const int searchNum = 2;
    int arr[count] = {1,2,3,5,6};
    bool isInserted = tree.InsertArr(arr, count);
    EXPECT_TRUE(isInserted);
    Node* insertNode = tree.Find(searchNum);
    Node* resultNode = tree.Find(searchNum);
    EXPECT_EQ(resultNode->number, searchNum);
}

TEST(TestCase1, FindFalse){
    BinaryTree tree;
    const int count = 5;
    const int searchNum = 7;
    int arr[count] = {1,2,3,5,6};
    bool isInserted = tree.InsertArr(arr, count);
    EXPECT_TRUE(isInserted);
    Node* resultNode = tree.Find(searchNum);
    EXPECT_FALSE(resultNode);

}

TEST(TestCase1, DeleteWithNoChildren){
    BinaryTree tree;
    const int count = 5;
    const int delNum = 6;
    int arr[count] = {1,2,3,5,6};
    bool isInserted = tree.InsertArr(arr, count);
    EXPECT_TRUE(isInserted);
    Node* insertNode = tree.Find(delNum);
    EXPECT_EQ(insertNode->number, delNum); 
    bool isDeleted = tree.Delete(delNum);
    EXPECT_TRUE(isDeleted);
    Node* delNode = tree.Find(delNum);
    EXPECT_FALSE(delNode);
}


TEST(TestCase1, DeleteWithOneChild){
    BinaryTree tree;
    const int count = 5;
    const int delNum = 4;
    const int delChildNum = 5;
    int arr[count] = {3,2,1,4,5};
    bool isInserted = tree.InsertArr(arr, count);
    Node* insertNode = tree.Find(delNum);
    EXPECT_EQ(insertNode->number, delNum); 
    bool isDeleted = tree.Delete(delNum);
    EXPECT_TRUE(isDeleted);
    Node* delNode = tree.Find(delNum);
    EXPECT_FALSE(delNode);
    Node* delNodeChild = tree.Find(delChildNum);
    EXPECT_EQ(delNodeChild->number, delChildNum);
    EXPECT_EQ(delNodeChild->parent, tree._root);
    EXPECT_EQ(tree._root->right, delNodeChild);
}

TEST(TestCase1, DeleteWithBothChildrenLeftSubTree){
    BinaryTree tree;
    const int count = 5;
    const int delNum = 8;
    const int finalRootNumber = 7;
    int arr[count] = {8,13,5,7,6};
    bool isInserted = tree.InsertArr(arr, count);
    EXPECT_TRUE(isInserted);
    EXPECT_EQ(tree._root->number, delNum); 
    bool isDeleted = tree.Delete(delNum);
    EXPECT_TRUE(isDeleted);
    Node* delNode = tree.Find(delNum);
    EXPECT_FALSE(delNode);
    EXPECT_EQ(tree._root->number, finalRootNumber);

}

TEST(TestCase1, DeleteWithBothChildrenRightSubTree){
    BinaryTree tree;
    const int count = 5;
    const int delNum = 9;
    const int finalRootNumber = 10;
    int arr[count] = {9,5,13,10,12};
    bool isInserted = tree.InsertArr(arr, count);
    EXPECT_TRUE(isInserted);
    EXPECT_EQ(tree._root->number, delNum); 
    bool isDeleted = tree.Delete(delNum);
    EXPECT_TRUE(isDeleted);
    Node* delNode = tree.Find(delNum);
    EXPECT_FALSE(delNode);
    EXPECT_EQ(tree._root->number, finalRootNumber);
    Node* child = tree.Find(12);
    Node* parent = tree.Find(13);
    EXPECT_EQ(parent->left, child);
    EXPECT_EQ(child->parent, parent);

}

TEST(TestCase1, InsertWithRebalancePosFactorAndRightSubTree){
    BinaryTree tree(false);
    const int count = 5;
    int arr[count] = {3,1,5,4,6};
    int insertNum = 7;
    bool isInserted = tree.InsertArr(arr, count);
    EXPECT_TRUE(isInserted);
    isInserted = tree.Insert(insertNum);
    EXPECT_TRUE(isInserted);
    Node* insertedNode = tree.Find(insertNum);
    EXPECT_EQ(insertedNode->number, insertNum);
    Node* newRoot = tree.Find(5);
    EXPECT_EQ(tree._root, newRoot);
    Node* node4 = tree.Find(4);
    Node* node3 = tree.Find(3);
    EXPECT_EQ(node4->parent, node3); 
    EXPECT_EQ(node3->right, node4);
    EXPECT_EQ(node3->parent, newRoot);
    EXPECT_EQ(newRoot->left, node3);
    EXPECT_FALSE(newRoot->parent);

}

TEST(TestCase1, ClockwiseRotation){
    BinaryTree tree;
    const int count = 5;
    int arr[count] = {3,8,6,7,9};
    tree.InsertArr(arr, count);
    
    Node* node = tree.Find(6);
    Node* node8 = tree.Find(8);
    Node* node3 = tree.Find(3);
    Node* node7 = tree.Find(7);

    tree.RotationClockwise(node);
    EXPECT_EQ(node->parent, node3); 
    EXPECT_EQ(node->right, node8);
    EXPECT_EQ(node7->parent, node8);
    EXPECT_EQ(node8->left, node7);
    EXPECT_EQ(node8->parent, node);
    //does not make check for balancefactors as the tree is unbalanced before insertion
}

TEST(TestCase1, InsertWithDoubleRotation){
    BinaryTree tree(false);
    const int count = 5;
    const int insertNum = 4;
    int arr[count] = {3,1,8,9,5};
    tree.InsertArr(arr, count);
    bool isInserted = tree.Insert(insertNum); 
    EXPECT_TRUE(isInserted);
    Node* node4 = tree.Find(insertNum);
    Node* node3 = tree.Find(3);
    Node* node8 = tree.Find(8);
    Node* node5 = tree.Find(5);

    EXPECT_EQ(tree._root, node5);
    EXPECT_EQ(node5->left, node3); 
    EXPECT_EQ(node5->right, node8);
    EXPECT_EQ(node4->parent, node3);
    EXPECT_FALSE(node8->left);
    EXPECT_EQ(node8->parent, node5);
    EXPECT_EQ(node8->balancefactor, 1);
    EXPECT_EQ(node3->balancefactor, 0);
    EXPECT_EQ(node5->balancefactor, 0);
    
}

TEST(TestCase1, InsertLeftSubTreeSingleRotation){
    BinaryTree tree(false);
    const int count = 5;
    const int insertNum = 1;
    int arr[count] = {5, 3, 6, 4, 2};
    tree.InsertArr(arr, count);
    bool isInserted = tree.Insert(insertNum); 
    EXPECT_TRUE(isInserted);
    Node* node3 = tree.Find(3);
    Node* node4 = tree.Find(4);
    Node* node5 = tree.Find(5);

    EXPECT_EQ(tree._root, node3);

    EXPECT_EQ(node3->right, node5); 
    EXPECT_FALSE(node3->parent);
    EXPECT_EQ(node3->balancefactor, 0);
    
    EXPECT_EQ(node5->balancefactor, 0);
    EXPECT_EQ(node5->left, node4);
    EXPECT_EQ(node5->parent, node3);

    EXPECT_EQ(node4->parent, node5);
    
}

TEST(TestCase1, InsertLeftSubTreeDoubleRotationInner){
    BinaryTree tree(false);
    const int count = 5;
    const int insertNum = 6;
    int arr[count] = {7,3,8,2,5};
    tree.InsertArr(arr, count);
    bool isInserted = tree.Insert(insertNum); 
    EXPECT_TRUE(isInserted);
    Node* node3 = tree.Find(3);
    Node* node5 = tree.Find(5);
    Node* node6 = tree.Find(6);
    Node* node7 = tree.Find(7);
    Node* node8 = tree.Find(8);

    EXPECT_EQ(tree._root, node5);

    EXPECT_EQ(node5->left, node3); 
    EXPECT_EQ(node5->right, node7);
    EXPECT_FALSE(node5->parent); 
    EXPECT_EQ(node5->balancefactor, 0);

    EXPECT_FALSE(node3->right);
    EXPECT_EQ(node3->parent, node5);
    EXPECT_EQ(node3->balancefactor, -1);

    EXPECT_EQ(node7->left, node6);
    EXPECT_EQ(node7->parent, node5);
    EXPECT_EQ(node7->balancefactor, 0);

}

TEST(TestCase1, InsertLeftSubTreeDoubleRotationOuter){
    BinaryTree tree(false);
    const int count = 5;
    const int insertNum = 4;
    int arr[count] = {7,3,8,2,5};
    tree.InsertArr(arr, count);
    bool isInserted = tree.Insert(insertNum); 
    EXPECT_TRUE(isInserted);
    Node* node3 = tree.Find(3);
    Node* node5 = tree.Find(5);
    Node* node4 = tree.Find(4);
    Node* node7 = tree.Find(7);
    Node* node8 = tree.Find(8);

    EXPECT_EQ(tree._root, node5);

    EXPECT_EQ(node5->left, node3); 
    EXPECT_EQ(node5->right, node7);
    EXPECT_FALSE(node5->parent); 
    EXPECT_EQ(node5->balancefactor, 0);

    EXPECT_EQ(node3->right, node4);
    EXPECT_EQ(node3->parent, node5);
    EXPECT_EQ(node3->balancefactor, 0);

    EXPECT_FALSE(node7->left);
    EXPECT_EQ(node7->parent, node5);
    EXPECT_EQ(node7->balancefactor, 1);

}

}