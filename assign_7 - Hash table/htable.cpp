// ====================================================
// Your name: Tyler Felicidario
// Complier:  g++
// File type: htable.cpp implementation file
//=====================================================

#include "htable.h"

/**
 * @brief Constructor to create an empty hash table
 * @param size The number of buckets in the hash table
 */
HashTable::HashTable(int size)
{
	table_size = size;
	table = vector<LinkedList>(size);
}

/**
 * @brief Destructor
 */
HashTable::~HashTable()
{
	for (int i = 0; i < table_size; i++) {
		unsigned int vecSize = table.size();
		for (unsigned int j = 0; j < vecSize; j++) {
			table.clear();
		}
	}
}
/**
 * @brief  Get the hash key of the order
 * @return int The hashed index of the order ID
 */
int HashTable::hash(int id)
{
	return id % table_size;
}

/**
 * @brief Find an order by its ID
 * @param id: the order ID
 * @param order: the reference to stored found order (if found)
 * @return true if found, false otherwise
 */
bool HashTable::findOrder(int id, Order &order)
{
	int index = hash(id);
	Node* newNode = table[index].getFront();
	
	if (table[index].isEmpty()) {
		return false;
	}
	else {
		while (newNode != nullptr) {
			// If newNode's order contains the id to search for
			if (newNode->val.id == id) {
				order = newNode->val;
				return true;
			}

			newNode = newNode->next;
		}
		return false;
	}
}

/**
 * @brief Insert an order into the hash table. The order ID is used as the key.
 * A order is inserted only if its ID isn't in the table
 * @return true if inserted, false otherwise
 */
bool HashTable::insertOrder(const Order& order) {
	Order new_order;
	int index = hash(order.id);
	
	if (findOrder(order.id, new_order) == true) {
		return false;
	}
	else {
		table[index].addRear(order);
		return true;
	}
}

/**
 * @brief Load orders from a file
 * 
 * @param file_name The name of the file to load
 */
void HashTable::fillTable(string file_name) {
	// Open the file to read
	Order order;
	ifstream fin;
	fin.open(file_name.c_str());
	if (!fin) {
		cout << "Error opening file " << file_name << endl;
		return;
	}
	while (fin >> order) {
		insertOrder(order);	
	}
	
	fin.close();
}


/**
 * @brief Remove an order from the hash table. The order ID is used as the key.
 *        A order is removed only if its ID is in the table
 * 
 * @param id 
 * @return true if the order is removed, false otherwise
 */ 
bool HashTable::removeOrder(int id) {
	Order removed_order;
	int index = hash(id);

	if (findOrder(id, removed_order) == true) {	
		int pos = table[index].search(removed_order);
		if (pos == -1) {
			return false;
		}
		else if (table[index].deleteAt(pos, removed_order))
			return true;
	}
	return false;
}

// Display the hash table
void HashTable::printTable() {
	for (int i = 0; i < table_size; i++) {
		cout << "Bucket " << i << ": ";
		table[i].displayAll();
	}
}

/**
 * @brief Get the total number of orders in the hash table
 * 
 * @return int The number of orders in the hash table
 */
int HashTable::numOrders() const {
	int count = 0;
	for (int i = 0; i < table_size; i++) {
		count += table[i].length();
	}
	return count;
}

// Update the order in the hash table
/**
 * @brief Update a order in the hash table. The order ID is used as the key.
 * 		  A order is updated only if its ID is in the table
 * @param order the new order that is used to update the old order 
 * @return true if the order is updated, false otherwise
 */
bool HashTable::updateOrder(const Order& order) {
	Order check;
	if (findOrder(order.id, check) == true) {
		int index = hash(order.id);
		int pos = table[index].search(order);
		Node* p = table[index].getNode(pos);
		p->val = order;
	}
	else
		return false;

	return true;
}

/**
* @brief Helper function for rehash; checks if a prime number
* 
* @return true or false if it's a prime number or not
*/
bool isPrime(int num) {
    // Corner case
    if (num <= 1)
        return false;
 
    // Check from 2 to n-1
    for (int i = 2; i < num; i++)
        if (num % i == 0)
            return false;
 
    return true;
}

/**
 * @brief Rehash the hash table to a new size. The orders are rehashed to the new table
 * 
 * @param new_size The new number of buckets in the hash table
 */
void HashTable::rehash(int new_size) {
	int old_size = table_size;
	//	Resize table_size
	table_size *= 2;
	
	while (!isPrime(table_size)) {
		table_size++;
	}
	vector<LinkedList> new_table(new_size);
	int iter = 0;
	
	//	Iterate through old table
	while (iter != old_size) {
		Node* p = table[iter].getFront();
		// Iterating through LL at table[iter]
		while (p != nullptr) {
			//	Rehash the id
			int pos = hash(p->val.id);
			//	At new_table[pos] add new item
			new_table[pos].addRear(p->val);
			p = p->next;
		}
		iter++;
	}

	table = new_table;
}
