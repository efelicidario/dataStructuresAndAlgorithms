/**
 * @brief Implementation of unionLinkedList and mergeLinkedList functions
 */

#include "linkedlist.h"

/**
    * @brief Assume two linked lists that represent Set A and Set B respectively.
    * Compute the union A U B and return the result as a new linked list.
    *
    * @param LA Input linkedlist A as a set (no duplicated element)
    * @param LB Input linkedlist B as a set (no duplicated element)
    * @return LinkedList return the unioned linkedlist 
    */
LinkedList unionLinkedList(const LinkedList& LA, const LinkedList& LB) {
    // Starting w/ empty linked list:
    LinkedList LC;
    LC = LA;
    Node* iter = LB.front;
    while (iter != nullptr) {
        if (LC.search(iter->val) == -1) {
            LC.addRear(iter->val);
        }
        iter = iter->next;
    }
    return LC;
}

/**
     * @brief Assume two input linked lists, LA and LB, whose elements are both in the non-descending order.
     * This function merges LA and LB into a new linked list (as the return value).
     * The elements in the new list should still be in the non-descending order.
     *
     * @param LA
     * @param LB
     * @return LinkedList
     */
LinkedList mergeLinkedList(const LinkedList& LA, const LinkedList& LB) {
    LinkedList LC;  // Create the new list
    Node* iterA = LA.front;
    Node* iterB = LB.front;
    
    while (iterA != nullptr && iterB != nullptr) {  // Bounds check
        if (iterA->val <= iterB->val) {     // Special case
            LC.addRear(iterA->val);
            iterA = iterA->next;
        }
        else if (iterA->val > iterB->val) { // Normal case
            LC.addRear(iterB->val);
            iterB = iterB->next;
        }
    }
    while (iterA != nullptr) {  // Iterate through list A
        LC.addRear(iterA->val); // addRear() to the new list, C
        iterA = iterA->next;    // Point to next element in list A
    }
    while (iterB != nullptr) {  // Iterate through list B
        LC.addRear(iterB->val); // addRear() to new list, C
        iterB = iterB->next;    // Point to next element in list B
    }
    return LC;
}
