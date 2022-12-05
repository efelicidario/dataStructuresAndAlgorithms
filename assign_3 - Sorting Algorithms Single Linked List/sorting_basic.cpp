/**
 * Implemention of selected sorting algorithms
 * @file sorting.cpp
 */

#include "sorting.h"

/**
 * Implement the insertionSort algorithm correctly
 */
void insertionSort(int array[], int lowindex, int highindex, bool reversed) {
    if (!reversed) {
        for (int i = 1; i < highindex + 1; i++) {
            int j = i;
            while (j > 0 && array[j] < array[j - 1]) {
                // Swap array[j] and array[j - 1]
                int temp = array[j];
                array[j] = array[j - 1];
                array[j - 1] = temp;
                j--;
            }
        }
    }
    else {
        for (int i = 1; i < highindex + 1; i++) {
            int j = i;
            while (j > 0 && array[j] > array[j - 1]) {
                // Swap array[j] and array[j - 1]
                int temp = array[j];
                array[j] = array[j - 1];
                array[j - 1] = temp;
                j--;
            }
        }
    }
}

/**
 * @brief Implementation of the partition function used by quick sort
 * 
 */
int partition(int array[], int lowindex, int highindex, bool reversed) {
    // Select the middle value as the pivot.
    int midpoint = lowindex + (highindex - lowindex) / 2;
    int pivot = array[midpoint];

    // "low" and "high" start at the ends of the partition
    // and move toward each other.
    int low = lowindex;
    int high = highindex;

    bool done = false;
    while (!done) {

        if (!reversed) {
            // Increment low while array[low] < pivot
            while (array[low] < pivot) {
                low += 1;
            }
            // Decrement high while pivot < array[high]
            while (pivot < array[high]) {
                high -= 1;
            }
        }
        else {
            // Increment low while array[low] > pivot
            while (array[low] > pivot) {
                low += 1;
            }
            // Decrement high while pivot > array[high]
            while (pivot > array[high]) {
                high -= 1;
            }
        }

        // If low and high have crossed each other, the loop
        // is done. If not, the elements are swapped, low is
        // incremented and high is decremented.
        if (low >= high) {
            done = true;
        }
        else {
            int temp = array[low];
            array[low] = array[high];
            array[high] = temp;
            low += 1;
            high -= 1;
        }
    }

    // "high" is the last index in the left partition.
    return high;
}

/**
 * Implement the quickSort algorithm correctly
 */
void quickSort(int array[], int lowindex, int highindex, bool reversed) {
    // Only sort if at least 2 elements exist.
    if (highindex <= lowindex) {
        return;
    }

    // Partition the array
    int high = partition(array, lowindex, highindex, reversed);

    // Recursively sort the left partition
    quickSort(array, lowindex, high, reversed);

    // Recursively sort the right partition
    quickSort(array, high + 1, highindex, reversed);
}


