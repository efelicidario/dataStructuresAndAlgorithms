//CS 311 Zhang F'22 Linked List class

//INSTRUCTION:
//It helps to first create if-then-else structure to fill in later.
//- Make sure PURPOSE and PARAMETER comments are given in detail
//  Highly recommended to copy HW3P1-help as PURPOSE of each function.
//  Add sufficient comments to your code body to describe what it does.
//      - Make sure all if-then-else are commented describing which case it is
//      - Make sure all local variables are described fully with their purposes


// ====================================================
//Your name: Tyler Felicidario
//Complier:  g++
//File type: linkedList.cpp implementation file
//=====================================================

#include<iostream>
#include"linkedlist.h"

using namespace std;

/**
 * @brief Destructor to destroy all nodes and release memory
 */
LinkedList::~LinkedList() {
    Node* curNode = front;  // curNode holds front node
    while (curNode != nullptr) {    // iterate through the list
        Node* toBeDeleted = curNode;
        curNode = curNode->next;
        delete toBeDeleted;
    }
}

/**
 * @brief Purpose: Checks if the list is empty
 * @return true if the list is empty, false otherwise
 */
bool LinkedList::isEmpty() const {
    if (front == nullptr) {
        // If front is nullptr (empty),
        // we can conclude that the list is empty
        return true;
    }
    else {
        // Otherwise
        return false;
    }
} 

/**
 * @brief  Get the number of nodes in the list
 * @return int The number of nodes in the list
 */
int LinkedList::length() const{
    // create a temp node 
    // to store the front node in
    Node* curNode = front;
    int count = 0; // count holds the length of the list
    while (curNode) {   // iterate through list
        count ++;
        curNode = curNode->next;
    }
    return count;   // return the list length
}

/**
 * @brief Convert the list to a string
 *
 */
string LinkedList::toString() {
    string str = "[";
    Node *ptr = front;
    if (ptr != nullptr) {
        // Head node is not preceded by separator
        str += to_string(ptr->val);
        ptr = ptr->next;
    }
    while (ptr != nullptr) {
        str += ", " + to_string(ptr->val);
        ptr = ptr->next;
    }
    str  += "]";
    return str;
}

/**
 * @brief Displays the contents of the list
 */
void LinkedList::displayAll() {
    cout << toString() << endl;
}

void LinkedList::addRear(T val) {
    // Create a new node containing the value to append
    Node* newNode = new Node(val);
    if (front == nullptr) {
        // if list is empty,
        // new node is the front and rear
        front = newNode;
        rear = newNode;
    }
    else {
        // otherwise,
        rear->next = newNode;
        rear = newNode;
    }
    count += 1;
}

void LinkedList::addFront(T val) {
    Node* newNode = new Node(val);  // new Node w/ value to prepend
    if (front == nullptr) { // if list is empty, 
        front = newNode;    // newNode is the first node in the list
        rear = newNode;
    }
    else {
        // otherwise,
        // store front into new node's successor
        newNode->next = front;
        // new node becomes front
        front = newNode;
    }
    count += 1;
} 

bool LinkedList::deleteFront(T &OldNum) {
    if (isEmpty() == true) {
        // return false if list is empty
        return false;
    }
    Node* curNode = front;
    if (front->next == nullptr) { // Case: if list contains only one element
        curNode = front;
        front = nullptr;
    }
    else {
        // if list contains more than one element
        curNode = front;
        front = front->next;
    }
    OldNum = curNode->val;  // OldNum reference variable 
    delete curNode;
    count -= 1;
    return true;            // to output the deleted value
} 

bool LinkedList::deleteRear(T &OldNum) {
    Node* curNode = front;
    Node* preNode = front;
    if (isEmpty() == true) {    // Case: if list is empty
        return false;
    }
    else if (front->next == nullptr) {  // Case: only one node in the list
        curNode = front;
        front = nullptr;
    }
    else {  // Normal case:
        curNode = front;
        while (curNode->next != nullptr) {  // iterate through list to find the last node
            preNode = curNode;
            curNode = curNode->next;
        }
        rear = preNode;             // make the preNode the rear
        preNode->next = nullptr;
    }
    OldNum = curNode->val;  // Updates reference variable 
    delete curNode;
    count -= 1;
    return true;
} 

/* --- harder ones for test 2 and 3 -- */

/**
     * @brief Delete a node at a given position from the list. The
     * node at position pos is deleted and the value of the deleted node is returned in val.
     * The valid range of pos is 1 to count. pos = 1 is the first node, and pos = count is the last node.
     * @param pos: position of the node to be deleted
     * @param val: it is set to the value of the node to be deleted
     * @return true: if the node was deleted successfully
     * @return false: if the node was not deleted successfully because the position was out of range
    */

bool LinkedList::deleteAt(int pos, T &val) {
    if (pos < 0 || pos >= count) {  // Case: if pos is negative or larger than count.
        return false;
    }
    if (pos == 0) { // Case: if pos is the first in the list.
        deleteFront(val);
        return true;
    }
    else if (pos == length()-1) {   // Case: if pos is at the end of the list
        deleteRear(val);
        return true;
    }
    else {  // Otherwise, normal case:
        Node* temp = front;
        for (int i=1;i<pos;i++) {   // iterate through list
            if (temp != nullptr) {
                temp = temp->next;
            }
        }
        if (temp != nullptr && temp->next != nullptr) {
            Node* toBeDeleted = temp->next;
            temp->next = temp->next->next;
            val = toBeDeleted->val;
            delete toBeDeleted;
        }
        else {
            return false;
        }
        count -= 1;
        return true;
    }
}

/**
     * @brief Insert a value at a specified position in the list. The valid pos is in the range of 1 to count+1.
     * The value will be inserted before the node at the specified position. if pos = 1, the value will be inserted
     * at the front of the list. if pos = count+1, the value will be inserted at the rear of the list.
     * @param pos: position to insert the value at.
     * @param val: value to insert.
     * @return true: if the value was inserted.
     * @return false: if the value was not inserted because pos is out of the range.
     */

bool LinkedList::insertAt(int pos, T val) {if (pos < 0 || pos > count) {
        return false;
    }
    else if (pos == 0) {
        addFront(val);
        return true;
    }
    else if (pos == length() || pos == length()+1) {
        addRear(val);
        return true;
    }
    else {
        Node* preNode = front;
        Node* curNode = front;
        Node* newNode = new Node(val);

        for (int i=0;i<pos;i++) {
            preNode = curNode;
            curNode = curNode->next;
        }

        preNode->next = newNode;
        newNode->next = curNode;
        count += 1;
        return true;
    }
}

/**
 * @brief Copy Constructor to allow pass by value and return by value of a LinkedList
 * @param other LinkedList to be copied
 */
LinkedList::LinkedList(const LinkedList &other) {
    // Start with an empty list
    front = nullptr;
    rear = nullptr;
    count = 0;

    Node* iter = other.front;
        // Interate through the other list and add a new node to this list
        while (iter != nullptr) {
            // Be sure to set the front and rear pointers to the correct values
            // Be sure to set the count to the correct value
            addRear(iter->val);
            iter = iter->next;
        }
}

/**
 * @brief Overloading of = (returns a reference to a LinkedList)
 * @param other LinkedList to be copied
 * @return reference to a LinkedList
 */
LinkedList &LinkedList::operator=(const LinkedList &other) {
    if(this != &other) { // check if the same object
        // Delete all nodes in this list
        while (!isEmpty()) {
            int x;
            deleteFront(x);
        }
        count = 0;
        Node* iter = other.front;
        // Interate through the other list and add a new node to this list
        while (iter != nullptr) {
            // Be sure to set the front and rear pointers to the correct values
            // Be sure to set the count to the correct value
            addRear(iter->val);
            iter = iter->next;
        }
    }
    return *this;
}

/**
 * Implement the search function.
 * 
 * @return int: the position of the value in the list. If the value is not in the list, return -1.
 */
 int LinkedList::search(const T& val) const {
    Node* searchNum = nullptr;
    Node* temp = front;
    Node* curNode = front;
    int counter = 0;

    while (curNode != nullptr && curNode->val != val) { // Validity / Bounds checking
        temp = curNode;
        curNode = curNode->next;
        counter += 1;
    }
    if (curNode != nullptr) {
        searchNum = curNode;
        curNode = curNode->next;
        return counter;
    }
    else {  // returning -1 if the value isn't in the list
        return -1;
    }
}