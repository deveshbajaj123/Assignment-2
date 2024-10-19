#include <iostream>
#include <vector>

class HashTable {
private:
    std::vector<int> table;
    std::vector<bool> deleted;
    int currentSize;
    int capacity;
    float loadFactorThreshold = 0.8; 
    int size;

    
    int hashFunction(int key) const {
        return key % capacity;
    }

    
    void resizeTable() {
        int oldCapacity = capacity;
        capacity *= 2;  
        std::vector<int> oldTable = table;
        std::vector<bool> oldDeleted = deleted;

        table.clear();
        table.resize(capacity, -1);
        deleted.clear();
        deleted.resize(capacity, false);
        currentSize = 0;

        
        for (int i = 0; i < oldCapacity; i++) {
            if (oldTable[i] != -1 && !oldDeleted[i]) {
                insert(oldTable[i]);
            }
        }
    }

    
    int quadraticProbing(int hash, int i) const {
        return (hash + i * i) % capacity;
    }

public:
   
    HashTable(int initialSize) : capacity(initialSize), currentSize(0) {
        table.resize(initialSize, -1); 
        deleted.resize(initialSize, false); 
    }

   
    void insert(int key) {
        
        if ((float)(currentSize + 1) / capacity > loadFactorThreshold) {
            resizeTable();
        }

        int hash = hashFunction(key);
        int i = 0;
        while (table[quadraticProbing(hash, i)] != -1 && !deleted[quadraticProbing(hash, i)]) {
            i++;
        }

        table[quadraticProbing(hash, i)] = key;
        deleted[quadraticProbing(hash, i)] = false;
        currentSize++;
    }

    
    int search(int key) {
        int hash = hashFunction(key);
        int i = 0;
        while (table[quadraticProbing(hash, i)] != -1) {
            if (table[quadraticProbing(hash, i)] == key && !deleted[quadraticProbing(hash, i)]) {
                return quadraticProbing(hash, i);
            }
            i++;
        }
        return -1; 
    }

   
    void remove(int key) {
        int hash = hashFunction(key);
        int i = 0;
        while (table[quadraticProbing(hash, i)] != -1) {
            if (table[quadraticProbing(hash, i)] == key && !deleted[quadraticProbing(hash, i)]) {
                deleted[quadraticProbing(hash, i)] = true;
                currentSize--;
                return;
            }
            i++;
        }
    }

    
    void printTable() const {
        
        for (int i = 0; i < capacity; i++) {
            if (table[i] != -1 && !deleted[i]) {
                std::cout << table[i] << " ";
            } else {
                std::cout << "- ";
            }
        }
        std::cout << std::endl;
    }
};

