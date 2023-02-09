#include "hashtable.h"
#include <stdlib.h>

/*
 * This creates a new hash table of the specified size and with
 * the given hash function and comparison function.
 */
HashTable *createHashTable(int size, unsigned int (*hashFunction)(void *),
                           int (*equalFunction)(void *, void *)) {
  int i = 0;
  HashTable *newTable = malloc(sizeof(HashTable));
  newTable->size = size;
  newTable->data = malloc(sizeof(struct HashBucket *) * size);
  for (i = 0; i < size; ++i) {
    newTable->data[i] = NULL;
  }
  newTable->hashFunction = hashFunction;
  newTable->equalFunction = equalFunction;
  return newTable;
}

int getLocation(HashTable *table, void *key) {
  return table->hashFunction(key) % table->size;
}

/*
 * This inserts a key/data pair into a hash table.  To use this
 * to store strings, simply cast the char * to a void * (e.g., to store
 * the string referred to by the declaration char *string, you would
 * call insertData(someHashTable, (void *) string, (void *) string).
 * Because we only need a set data structure for this spell checker,
 * we can use the string as both the key and data.
 */
void insertData(HashTable *table, void *key, void *data) {
  // Find the right hash bucket location with table->hashFunction.
  int location = getLocation(table, key);
  // Allocate a new hash bucket struct.
  PtrToBucket newBucket = malloc(sizeof(struct HashBucket));
  newBucket->key = key;
  newBucket->data = data;
  // Append to the linked list or create it if it does not yet exist. 
  newBucket->next = (table->data)[location];
  (table->data)[location] = newBucket;
}

/*
 * This returns the corresponding data for a given key.
 * It returns NULL if the key is not found. 
 */
void *findData(HashTable *table, void *key) {
  // Find the right hash bucket with table->hashFunction.
  PtrToBucket cursor = table->data[getLocation(table, key)];
  // Walk the linked list and check for equality with table->equalFunction.
  while (cursor != NULL) {
    if (cursor->key == key) {
      return cursor->data;
    }
    cursor = cursor->next;
  }
  return NULL;
}