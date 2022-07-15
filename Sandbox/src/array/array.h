////////////////////////////////////////////////////////////
//
// Last Straw Labs, Inc.
// www.laststrawlabs.com
// July 9, 2022
//
////////////////////////////////////////////////////////////
#ifndef ARRAY_H
#define ARRAY_H


#include <stdlib.h>
#include <string.h>


// structure
typedef struct list
{
  int count;
  int max;
  size_t isize;
  void* items;
} list;

// declaration
struct list* list_new(size_t size);
void   list_free(struct list* list);

void* list_add(struct list* list, void* item);
void  list_rm(struct list* list, void* item);

void* list_get(struct list* list, int item);
void* list_set(struct list* list, int num, void* item);

// testing
void test_main();


#endif // ARRAY_H


///////////////////////////
// EOF
///////////////////////////
