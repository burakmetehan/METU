#include "HashTable.h"

#include <cassert>
#include <iostream>
#include <iomanip>

const int KeyedHashTable::PRIME_LIST[PRIME_TABLE_COUNT] = {
      2,   3,   5,   7,  11,  13,  17,  19,
     23,  29,  31,  37,  41,  43,  47,  53,
     59,  61,  67,  71,  73,  79,  83,  89,
     97, 101, 103, 107, 109, 113, 127, 131,
    137, 139, 149, 151, 157, 163, 167, 173,
    179, 181, 191, 193, 197, 199, 211, 223,
    227, 229, 233, 239, 241, 251, 257, 263,
    269, 271, 277, 281, 283, 293, 307, 311,
    313, 317, 331, 337, 347, 349, 353, 359,
    367, 373, 379, 383, 389, 397, 401, 409,
    419, 421, 431, 433, 439, 443, 449, 457,
    461, 463, 467, 479, 487, 491, 499, 503,
    509, 521, 523, 541
};

int KeyedHashTable::Hash(const std::string& key) const
{
    int i, hash = 0;

    for (i = 0; i < key.length(); i++) {
        hash += key[i] * PRIME_LIST[i];
    }

    hash %= tableSize;

    if (hash < 0) { // in case overflow
        hash += tableSize;
    }else;

    return hash;
}

void KeyedHashTable::ReHash()
{
    int i, old_size = tableSize;
    HashData *old_table = new HashData[old_size];

    for (i = 0; i < old_size; i++) {
        old_table[i].key = table[i].key;
        old_table[i].intArray = table[i].intArray;
    }

    // Reset the values
    delete[] table;
    occupiedElementCount = 0; // Will be updated while inserting

    // Updating the values according to instructions
    tableSize = FindNearestLargerPrime(2 * old_size);
    table = new HashData[tableSize];

    // Inserting old items by using Insert()
    for (i = 0; i < old_size; i++)
    {
        if (old_table[i].key != "" && old_table[i].key != "__DELETED__") {
            Insert(old_table[i].key, old_table[i].intArray);
        }else;
    }

    // Freeing allocated memory
    delete[] old_table;
}

int KeyedHashTable::FindNearestLargerPrime(int requestedCapacity)
{
    int i;

    for (i = 0; i < PRIME_TABLE_COUNT; i++)
    {
        if (PRIME_LIST[i] > requestedCapacity) {
            return PRIME_LIST[i];
        }else;
    }

    return PRIME_LIST[PRIME_TABLE_COUNT-1];
}

KeyedHashTable::KeyedHashTable()
{
    tableSize = 2;
    occupiedElementCount = 0;
    table = new HashData[tableSize];
}

KeyedHashTable::KeyedHashTable(int requestedCapacity)
{
    tableSize = FindNearestLargerPrime(requestedCapacity);
    occupiedElementCount = 0;
    table = new HashData[tableSize];
}

KeyedHashTable::KeyedHashTable(const KeyedHashTable& other)
{
    int i;

    // Copying the table
    tableSize = other.tableSize;
    occupiedElementCount = other.occupiedElementCount;
    table = new HashData[tableSize];
    
    for (i = 0; i < tableSize; i++)
    {
        table[i].key = other.table[i].key;
        table[i].intArray = other.table[i].intArray;
    }
}

KeyedHashTable& KeyedHashTable::operator=(const KeyedHashTable& other)
{
    if (this != &other)
    {
        int i;

        // Deleting the existing table
        delete[] table;

        // Copying the table
        tableSize = other.tableSize;
        occupiedElementCount = other.occupiedElementCount;
        table = new HashData[tableSize];
        
        for (i = 0; i < tableSize; i++)
        {
            table[i].key = other.table[i].key;
            table[i].intArray = other.table[i].intArray;
        }
    }else;

    return *this;
}

KeyedHashTable::~KeyedHashTable()
{
    // Deleting the existing table
    delete[] table;
}

bool KeyedHashTable::Insert(const std::string& key, const std::vector<int>& intArray)
{
    int hash_index = Hash(key);

    if (table[hash_index].key == "" || table[hash_index].key == "__DELETED__") {
        occupiedElementCount++;
    }
    else
    {
        int i = 1, main_hash_index = hash_index;

        while (table[hash_index].key != "" && table[hash_index].key != "__DELETED__" && table[hash_index].key != key)
        {
            if (i >= tableSize) { // Control for INFINITE loop. (Most probably no chance for infinity loop)
                return false;
            }

            hash_index = main_hash_index + i*i; // quadratic probing
            hash_index %= tableSize;
            i++;
        }

        if (table[hash_index].key == key) { // same key, insertion fails
            return false;
        }
        else {
            occupiedElementCount++;
        }
    }

    // Inserting
    table[hash_index].key = key;
    table[hash_index].intArray = intArray;

    // Rehash check
    if (occupiedElementCount * EXPAND_THRESHOLD >= tableSize) {
        ReHash();
    }else;

    return true;
}

bool KeyedHashTable::Remove(const std::string& key)
{
    int i = 1, hash_index = Hash(key);
    int main_hash_index = hash_index;

    while (table[hash_index].key != key && table[hash_index].key != "") {
        if (i >= tableSize) { // Control for INFINITE loop. (Most probably no chance for infinity loop)
            return false;
        }

        hash_index = main_hash_index + i*i; // quadratic probing
        hash_index %= tableSize;
        i++;
    }

    if (table[hash_index].key == key) {
        occupiedElementCount--;
        table[hash_index].key = "__DELETED__";
        table[hash_index].intArray.clear();
        return true;
    }
    else {
        return false;
    }
}

void KeyedHashTable::ClearTable()
{
   int i;

   for (i = 0; i < tableSize; i++)
   {
       table[i].key = "";
       table[i].intArray.clear();
   }

   occupiedElementCount = 0;
}

bool KeyedHashTable::Find(std::vector<int>& valueOut, const std::string& key) const
{
    int i = 1, hash_index = Hash(key);
    int main_hash_index = hash_index;

    while (table[hash_index].key != key && table[hash_index].key != "") {
        if (i >= tableSize) { // Control for INFINITE loop. (Most probably no chance for infinity loop)
            return false;
        }

        hash_index = main_hash_index + i*i; // quadratic probing
        hash_index %= tableSize;
        i++;
    }

    if (table[hash_index].key == key) {
        valueOut = table[hash_index].intArray;
        return true;
    }
    else {
        return false;
    }
}

void KeyedHashTable::Print() const
{
    // ============================= //
    // This function is implemented  //
    // Do not edit this function !   //
    // ============================= //
    std::cout << "HT:";
    if(occupiedElementCount == 0)
    {
        std::cout << " Empty";
    }
    std::cout << "\n";
    for(int i = 0; i < tableSize; i++)
    {
        if(table[i].key == "") continue;

        std::cout << "[" << std::setw(3) << i << "] ";
        std::cout << "[" << table[i].key << "] ";
        std::cout << "[";
        for(size_t j = 0; j < table[i].intArray.size(); j++)
        {
            std::cout << table[i].intArray[j];
            if((j + 1) != table[i].intArray.size())
                std::cout << ", ";
        }
        std::cout << "]\n";
    }
    std::cout.flush();
}
