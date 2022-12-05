/**
 * @brief You will implement the insertion sort and merge sort algorithms for a linked list in this file
 */
//You should always comments to each function to describe its PURPOSE and PARAMETERS

#include "sorting.h"
#include <iostream>


Node* findInsertionPos(const LinkedList& list, int dataValue, int& counter, bool reversed) {
    Node* positionA = nullptr;
    Node* positionB = list.getFront();
    if (!reversed) {
        while (positionB != nullptr && dataValue > positionB->val) {    // iterate through the list with these conditions
            positionA = positionB;
            positionB = positionB->next;
            counter++;
        }                                                               // increment counter
    }
    else {
        while (positionB != nullptr && dataValue < positionB->val) {    // case: descending order
            positionA = positionB;
            positionB = positionB->next;
            counter++;
        }
    }
    return positionA;
}
/**
 * Implement the insertion sort algorithm for Linkedlist correctly
 */
LinkedList insertionSortLL(const LinkedList& list, bool reversed) {

    LinkedList copy(list);
    Node* preNode = copy.front;
    Node* curNode = copy.front->next;
    Node* nextNode = curNode->next;
    int counter;

    while (curNode != nullptr) {    // iterate through the list
        nextNode = curNode->next;
        Node* pos = findInsertionPos(copy, curNode->val, counter, reversed);
        if (pos == preNode) {
            preNode = curNode;
        }
        else {
            // Remove, but do not deallocate, curNode
            Node* sucNode = curNode->next;
            preNode->next = sucNode;
            if (sucNode == nullptr) {
                // Remove tail
                copy.rear = preNode;
            }
            curNode->next = nullptr;
            // Insert curNode back into list in sorted position
            if (pos == nullptr) {
                copy.addFront(curNode->val);
            }
            else {
                copy.insertAt(counter, curNode->val);
            }
        }
        curNode = nextNode;
    }
    return copy;
}

void FrontBackSplit(LinkedList& list, LinkedList& a, LinkedList& b) {   // Splits up the list into 2 separate lists and populates
    int mid = list.length() / 2;
    Node* iter = list.getFront();
    for(int i = 0; i < mid; i++) {  // populate the first half of the list, a
        a.addRear(iter->val);
        iter = iter->next;
    }
    while (iter != nullptr) {       // populate the other half of the list, b
        b.addRear(iter->val);
        iter = iter->next;
    }
}

void sortMerge(Node* a, Node* b, LinkedList &result) {

    if (a == nullptr && b == nullptr) {     // case: if lists are empty
        return;
    }
    else if (a == nullptr) {            // if list a is empty
        result.addRear(b->val);         // calling addRear() to list result
        sortMerge(a, b->next, result);  // recursive call to the function
    }
    else if (b == nullptr) {
        result.addRear(a->val);
        sortMerge(a->next, b, result);
    }
    else {                                      // normal case
        if (a->val >= b->val) {
            result.addRear(b->val);
            sortMerge(a, b->next, result);
        }
        else {
            result.addRear(a->val);
            sortMerge(a->next, b, result);
        }
    }
}

/**
 * Implement the merge sort algorithm for LinkedList correctly
 */
LinkedList mergeSortLL(const LinkedList& list, bool reversed) {

    LinkedList copy(list);  // move list
    LinkedList a;           // first half of list, a    
    LinkedList b;           // first half of list, b
    LinkedList result;      // result list

    if (copy.count == 0 || copy.count == 1) {
        return copy;
    }

    FrontBackSplit(copy, a, b);     // call to function to split the list

    mergeSortLL(a, false);          // recursively sort the partitions
    mergeSortLL(b, false);
    
    sortMerge(a.front, b.front, result);

    return result;
}
