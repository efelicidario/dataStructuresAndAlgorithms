/**
 * Implementation of BST class.
 */
//You should always comments to each function to describe its PURPOSE and PARAMETERS

// =======================================================
// Your name: Tyler Felicidario
// Compiler:  g++
// File type: cpp file BST.cpp
// @brief This class implements a BST search tree
//=======================================================

#include "BST.h"
#include <vector>
#include<iostream>

/**
 * Implement the BST constructor
 */
BST::BST() {
    root = nullptr;
    numElements = 0;
}

/**
 * Implement the BST destructor
 */
BST::~BST() {
    // Must release memory correctly to avoid memory leaks
    clear();
}

/**
 * Implement size() correctly
 */
unsigned int BST::size() const {
    return numElements;
}

/**
 * Helper function for clear() function
 */
void BST::deletePostorder(Node* node) {
    if (node != nullptr) {
        deletePostorder(node->leftChild);
        deletePostorder(node->rightChild);
        delete node;
        numElements--;
    }
}

/**
 * Implement clear() correctly without memory leaks
 */
void BST::clear() {
    deletePostorder(root);
    root = nullptr;
}

/**
 * Implement insert() correctly
 */
bool BST::insert(T element) {
    // First, check if tree is empty
    if (root == nullptr) {
        root = new Node(element);
        root->parent = nullptr;
        numElements++;
        return true;
    }
    else {
        Node *curNode = root;
        Node* newNode = new Node(element);

        while (curNode != nullptr) {
            if (newNode->data < curNode->data) {
                // If no left child exists, add the new node
                // here; otherwise repeat from the left child
                if (curNode->leftChild == nullptr) {
                    curNode->leftChild = newNode;
                    newNode->parent = curNode;
                    curNode = nullptr;
                }
                else {
                    curNode = curNode->leftChild;
                }
            }
            else if (newNode->data > curNode->data) {
                // If no right child exists, add the new node
                // here; otherwise repeat from the right child.
                if (curNode->rightChild == nullptr) {
                    curNode->rightChild = newNode;
                    newNode->parent = curNode;
                    curNode = nullptr;
                }
                else {
                    curNode = curNode->rightChild;
                }
            }
            else {
                // Checks for duplicate value
                delete newNode;
                return false;
            }
        }
        numElements++;
        return true;
    }
}

/**
 * Implement find() correctly
 */
bool BST::find(const T &query) const {
    Node* curNode = root;

    while (curNode != nullptr) {
        // Return Node if key matches
        if (curNode->data == query) {
            return true;
        }
        // Traverse down left subtree if search key is 
        // less than curNode's key
        else if (query < curNode->data) {
            curNode = curNode->leftChild;
        }
        // Traverse down right subtree if search key is
        // greater than curNode's key
        else {
            curNode = curNode->rightChild;
        }
    }
    // Key was not found in the tree
    return false;
}

/**
 * Helper function for height() function
 */
int BST::heightHelper(Node* node) const {

    if (node == nullptr ) {
        return -1;
    }
    else {
        int leftHeight = heightHelper(node->leftChild);
        int rightHeight = heightHelper(node->rightChild);

        if (leftHeight > rightHeight) {
            return leftHeight+1;
        }
        else
            return rightHeight+1;
    }
}

/**
 * Implement the height() function correctly
 */
int BST::height() const {
    return heightHelper(root);
}

/**
 * Implement the getRoot() function correctly
 */
BST::Node* BST::getRoot() {
    return root;
}

/**
 * @brief Print the subtree at node using inorder traversal
 * @param node a pointer to node in BST
 */
void BST::printInorder(Node* node) {
    if (node != nullptr) {
        printInorder(node->leftChild);
        std::cout << node->data << " ";
        printInorder(node->rightChild);
    }
}

/**
* @brief Print the subtree at node using preorder traversal
* @param node a pointer to node in BST
*/
void BST::printPreorder(Node* node) {
    if (node != nullptr) {
        // Visits this node
        std::cout << node->data << " ";
        printPreorder(node->leftChild);
        printPreorder(node->rightChild);
    }
}

/**
* @brief Print the subtree at node using postorder traversal
* @param node a pointer to node in BST
*/
void BST::printPostorder(Node* node) {
    if (node != nullptr) {
        printPostorder(node->leftChild);
        printPostorder(node->rightChild);
        // Visit this node
        std::cout << node->data << " ";
    }
}

/**
 * Implement the getLeftMostNode() function correctly
 */
BST::Node * BST::getLeftMostNode(Node * node) {
    Node* curNode = node;

    while (curNode->leftChild != nullptr) {
        curNode = curNode->leftChild; 
    }
    return curNode;
}

/**
 * Implement the getLeftMostNode() function correctly
 */
BST::Node* BST::getLeftMostNode() {
    return getLeftMostNode(root);
}

/**
 * Implement the BST successor function correctly
 */
BST::Node *BST::successor(Node *node) {
    if (node->rightChild != nullptr) {
        return getLeftMostNode(node->rightChild);
    }
    else {
        Node* curNode = node;
        while (curNode->parent != nullptr && curNode->parent->rightChild == curNode) {
            curNode = curNode->parent;
        }
        return curNode->parent;
    }
}

