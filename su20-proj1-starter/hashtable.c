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

/*
 * This creates a new hash bucket struct with the given key and data.
 */
PtrToBucket createBucket(void *key, void *data) {
  PtrToBucket result = malloc(sizeof(struct HashBucket));
  result->key = key;
  result->data = data;
  result->next = NULL;
  return result;
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
  int location = table->hashFunction(key) % table->size;
  // Allocate a new hash bucket struct.
  PtrToBucket newBucket = createBucket(key, data);
  // Append to the linked list.
  PtrToBucket oldHead = table->data[location];
  newBucket->next = oldHead;
  table->data[location] = newBucket;
}

/*
 * This returns the corresponding data for a given key.
 * It returns NULL if the key is not found. 
 */
void *findData(HashTable *table, void *key) {
  // Find the right hash bucket with table->hashFunction.
  int location = table->hashFunction(key) % table->size;
  // Walk the linked list and check for equality with table->equalFunction.
  PtrToBucket cursor = table->data[location];
  while (cursor != NULL) {
    if (table->equalFunction(cursor->key, key)) {
      return cursor->data;
    } else {
      cursor = cursor->next;
    }
  }
  return NULL;
}
