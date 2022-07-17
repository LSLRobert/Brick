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
typedef struct LS_List_ // list
{
  int count;
  int max;
  size_t isize;
  void* items;
} LS_List_, *LS_List;
//} list;

// declaration
LS_List list_new(size_t size);
void list_free(LS_List list);

void* list_add(LS_List list, void* item);
void  list_rm(LS_List list, void* item);

void* list_get(LS_List list, int num);
void* list_set(LS_List list, int num, void* item);

// testing
void test_main();


#endif // ARRAY_H


///////////////////////////
// EOF
///////////////////////////
