#include "heap.h"

// @brief gets the maximum value in the heap
// @return the highest value integer in the heap
T Heap::getMax() const {
    // If heap is empty, return -1
    if (count == 0)
        return -1;
    else
        return heaparray[0];
}


// @brief default constructor. Construct an empty heap with initial capacity
Heap::Heap(int capacity) {
    heaparray = new T[capacity];
    this->capacity = capacity;
    count = 0;
}
mme
// @brief destructor
Heap::~Heap() {
    delete[] heaparray;
}

/**
 * @brief constructor to build a heap from an array of values
 * @param values array of values to be added to the heap
 * @param length the size of the array
 */
Heap::Heap(T *values, int length) {
    this->heaparray = new T[length]; 
    this->capacity = length;
    this->count = length;
    for (int i = 0; i < length; i++) {
        heaparray[i] = values[i];
    }
    heapify();
}

/**
 * @brief Copy constructor
 * @param other the heap to be copied
 */
Heap::Heap(const Heap &other) {
    //this->heaparray = new T[other.count];
    this->heaparray = new T[other.capacity];
    this->capacity = other.capacity;
    this->count = other.count;
    
    for (int i = 0; i < other.count; i++) {
        this->heaparray[i] = other.heaparray[i];
    }
}

/**
 * @brief Assignment operator
 * @param other the heap to be copied
 * @return Heap& a reference to the heap
 */
Heap& Heap::operator = (const Heap &other) {
    if (this != &other) {
        delete[] this->heaparray;

        this->heaparray = new T[other.capacity];
        this->capacity = other.capacity;
        this->count = other.count;

        for (int i = 0; i < other.count; i++) {
            this->heaparray[i] = other.heaparray[i];
        }
    }
    return *this;
}

/**
 * @brief   organizes the values in the heap to satisfy heap property.
 */
void Heap::heapify() {
    for (int i = (count / 2) - 1; i >= 0; i--)
    {
        percolateDown(i);
    }
}

/**
 * @brief  Runs percolate down on the heap for the node stored in index.
 */
void Heap::percolateDown(int index) {
    int childIndex = 2 * index + 1;
    int value = heaparray[index];

    while (childIndex < count) {
        // Find the max among the node and all the node's children
        int maxValue = value;
        int maxIndex = -1;
        int i = 0;
        while (i < 2 && i + childIndex < count) {
            if (heaparray[i + childIndex] > maxValue) {
                maxValue = heaparray[i + childIndex];
                maxIndex = i + childIndex;
            }
            i++;
        }

        // Check for a violation of the max-heap property
        if (maxValue == value) {
            return;
        }
        else {
            // Swap heaparray[index] and heaparray[maxIndex]
            swap(index, maxIndex);

            // Continue loop from the max index node
            index = maxIndex;
            childIndex = 2 * index + 1;
        }
    }
}

/**
 * @brief  Runs percolate up on the heap for the node stored in index.
 */
void Heap::percolateUp(int index) {
    while (index > 0) {
        // Compute the parent node's index
            int parent = (index - 1) / 2;

        // Check for a violation of the max-heap property
        if (heaparray[index] <= heaparray[parent]) {
            // No violation, so percolate up is done
            return;
        }
        else {
            // Swap heaparray[index] and heaparray[parent]
            swap(index, parent);

            // Continue the loop from the parent node
            index = parent;
        }
    }
}

/**
 * @brief  inserts a value into the heap
 *
 */
void Heap::insert(T value) {
    if (count == capacity) {
        // Resize Heap array
        T* new_heaparray = new T[capacity * 2];
        for (int i = 0; i < count; i++) {
            new_heaparray[i] = heaparray[i];
        }
        capacity *= 2;
        delete[] heaparray;
        heaparray = new_heaparray;
    }
    else {
        // Add the new value to the end of the array
        heaparray[count] = value;
        count++;

        // Percolate up from the last index to restore the heap property
        percolateUp(count - 1);
    }
    
}

/**
 * @brief  Removes the max value from the heap
 * @return the value that was removed
 */
T Heap::removeMax() {
    // If heap is empty
    if (count == 0) {
        return -1;
    }
    else {
        // Save the max value from the root of the heap
        int maxValue = heaparray[0];

        // Move the last item in the array into index 0
        int replaceValue = heaparray[count - 1];
        count--;
        if (count > 0) {
            heaparray[0] = replaceValue;

            // Percolate down to restore max-heap property
            percolateDown(0);
        }

        // Return the max value
        return maxValue;
    }
}

//@brief converts the heap into a string
string Heap::toString()
{
    string s = "[ ";
    for (int i = 0; i < count; i++)
    {
        s += to_string(heaparray[i]) + " ";
    }
    s += "]";
    return s;
}

/**
 * @brief  Prints the values in the heap
 */
void Heap::printHeap() {
    cout << toString() << endl;
}

/**
 * @brief  Prints the values in an array
 */
void printArray(int values[], int length) {
    int i;
    cout << "[ ";
    for (i = 0; i < length; i++) {
        cout << values[i] << " ";
    }
    cout << "]\n";
}

/**
 * @brief  Swaps the values in the heap at index1 and index2
 */
void Heap::swap(int index1, int index2) {
    int temp = heaparray[index1];
    heaparray[index1] = heaparray[index2];
    heaparray[index2] = temp;
}

/**
 * @brief  Sorts the values of an array by using the heap
 */
void heapSort(T values[], int length) {
    cout << "Array Before Sorting: \n";
    printArray(values, length);

    // Use constructor to create tempHeap
    Heap tempHeap(values, length);  
    int i = length - 1;

    while (i != -1) {
        values[i] = tempHeap.removeMax();
        i--;
    }

    cout << "Array After Sorting: \n";
    printArray(values, length);

    return;
}

/**
     * @brief Change the key of the element at position i to the new value.
     *        It maintains the heap property.
     * @param i the position of the element to be decreased
     * @param new_val the new value
     */
void Heap::changeKey(int i, T new_val) {
    // Change key
    heaparray[i] = new_val;
    
    // Percolate to maintain heap property
    percolateDown(i);
    percolateUp(i);
}
