/*
* hash_table.hpp
* Written by : Lana Cossettini (c3436542)
* Modified : 29/10/2023
*
* This class represents a templated hash table that uses a binary search tree for chaining.
* It is assumed that data items contain the method get_key, which returns a string.
* This file is used in conjunction with Assignment 3 for SENG1120.
*/

template <typename T>
HashTable<T>::HashTable(int table_capacity) {
    capacity = table_capacity;
    table.resize(capacity);
    count = 0;
}

template <typename T>
HashTable<T>::~HashTable() {

}

// inserts element into hash table
template <typename T>
void HashTable<T>::insert(const T& data) {
    int location = hash_function(data.get_key()); //use hash function to detemine location
    table[location].insert(data);
    count++;
}

//removes given key from hash table
template <typename T>
void HashTable<T>::remove(const std::string& key) {
    int location = hash_function(key); //uses hash function to determine location
    table[location].remove(key);
    count--;
}


template <typename T>
T* HashTable<T>::get(const std::string& key) const {
    int location = hash_function(key); 
    return table[location].find(key); // finds and returns pointer to data with given key
}

// checks element with given key exists
template <typename T>
bool HashTable<T>::contains(const std::string& key) const {
    int location = hash_function(key);
    return table[location].contains(key);
}

template <typename T>
void HashTable<T>::clear() {
    for (int i = 0; i < capacity; ++i) {
        table[i].clear();
    }
    count = 0;
}

// checks if hash table is empty
template <typename T>
bool HashTable<T>::empty() const {
    return count == 0; 
}

// returns number of elements in table
template <typename T>
int HashTable<T>::size() const {
    return count;
}

// prints content of the table
template <typename T>
std::ostream& HashTable<T>::print(std::ostream& os) const {
    for (int i = 0; i < capacity; ++i) {
        os << i << ": " << table[i] << std::endl;
    }
    return os;
}

//Computes the hash function for the supplied string. returns location of given key
template <typename T>
int HashTable<T>::hash_function(const std::string& key) const {
    std::hash<std::string> hf;
    return hf(key) % capacity;
}


template <typename T>
std::ostream& operator<<(std::ostream& out, const HashTable<T>& hashTable) {
    return hashTable.print(out);
}
