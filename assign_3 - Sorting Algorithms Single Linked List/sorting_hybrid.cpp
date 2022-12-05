/**
 * @brief You will implement the "optimized" quick sort algorithms for a linked list in this file
 */
//You should always comments to each function to describe its PURPOSE and PARAMETERS
#include "sorting.h"

/**
 * Implement a hybrid of insertion sort and quick sort algorithm. The algorithm is based on the idea that if the array is short,
 * it is better to use insertion sort.
 * It uses quicksort until the list gets small enough, and then uses insertion sort or another sort to sort the small lists
 *
 */
void hybridQuickSort(int array[], int lowindex, int highindex, bool reversed) {
    int length = 0;
    for (int i = 0; i < highindex + 1; i++) {
        length++;
    }
    if (!reversed) {
        if (length <= 2) {
            insertionSort(array, lowindex, highindex, reversed);    // call insertionSort() if length is <= 2
        }
        else {
            quickSort(array, lowindex, highindex, reversed);        // otherwise 
        }
    }
    else {
        quickSort(array, lowindex, highindex, reversed);            // quickSort is reversed
    }
}