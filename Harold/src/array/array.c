////////////////////////////////////////////////////////////
//
// Last Straw Labs, Inc.
// www.laststrawlabs.com
// July 17, 2022
//
////////////////////////////////////////////////////////////
#include "header.h"
#include "array_int.h"


// LS_ListNew
LS_HAROLD_API LS_List LS_ListNew(LS_Memory arena, uSize size)
{
//  LS_List list = malloc(sizeof(struct LS_List_));
  LS_List list = LS_Malloc(arena, sizeof(struct LS_List_));
  list->isize = size;
  list->count = 0;
  list->max = 0;
  list->arena = arena;
  list->items = NULL;
}


// LS_ListFree
LS_HAROLD_API void LS_ListFree(LS_List list)
{
  LS_Free(list->arena, list->items);
  LS_Free(list->arena, list);
}


// LS_ListAdd
LS_HAROLD_API void* LS_ListAdd(LS_List list, void* item)
{
  u8* pos = NULL;
  
  if (list->items == NULL)
  {
//    list->items = malloc(list->isize);
    list->items = LS_Malloc(list->arena, list->isize);
    list->max = 1;
  }
  else if (list->count == list->max)
  {
    size_t size = list->isize * list->max * 2;
//    void* items = realloc(list->items, size);
    void* items = LS_Realloc(list->arena, list->items, size);
    if (items == NULL)
    {
      puts("realloc failed!");
      exit(EXIT_FAILURE);
    }
    list->items = items;
    list->max *= 2;
  }
  
  pos = (u8*)list->items + (list->count * list->isize);
  
  if (memcpy(pos, item, list->isize) == NULL)
  {
    puts("memccpy failed!");
    exit(EXIT_FAILURE);
  }
  
  list->count++;
  return pos;
}

// LS_ListRm
LS_HAROLD_API void LS_ListRm(LS_List list, void* item)
{
  u8* pos = (u8*)list->items;
  size_t tail_size = 0;
  
  for (int i=0; i < list->count; ++i)
  {
    if (memcmp(pos, item, list->isize) == 0) // 0 SUCCESS/NO_ERROR
    {
      tail_size = (list->max - (i + 1)) * list->isize;
      if (memcpy(pos, pos + list->isize, tail_size) == NULL)
      {
        puts("memccpy failed!");
        exit(EXIT_FAILURE);
      }
      list->count--;
      break;
    }
    pos += list->isize;
  }
  
  if (list->max > list->count * 2)
  {
    size_t size = list->isize * (list->max / 2);
//    void* items = realloc(list->items, size);
    void* items = LS_Realloc(list->arena, list->items, size);
    if (items == NULL)
    {
      puts("realloc failed!");
      exit(EXIT_FAILURE);
    }
    list->items = items;
    list->max /= 2;
  }
}

// LS_ListRemove
LS_HAROLD_API void LS_ListRemove(LS_List list, void* item)
{
  LS_ListRm(list, item);
}

// LS_ListGet
LS_HAROLD_API void* LS_ListGet(LS_List list, i32 num)
{
  u8* pos = NULL;
  if (num < 0 && num >= list->count)
  {
    printf("Array list out of bounds! Requesting: %d from %d\n", num + 1, list->count);
    exit(EXIT_FAILURE);
  }
  pos = (u8*)(list->items + (list->isize * num));
  return pos;
}

// LS_ListSet
LS_HAROLD_API void* LS_ListSet(LS_List list, i32 num, void* item)
{
  u8* pos = NULL;
  if (num < 0 && num >= list->count)
  {
    printf("Array list out of bounds! Requesting: %d from %d\n", num + 1, list->count);
    exit(EXIT_FAILURE);
  }
  pos = (u8*)(list->items + (list->isize * num));
  if (memcpy(pos, item, list->isize) == NULL)
  {
    puts("memccpy failed!");
    exit(EXIT_FAILURE);
  }
  return pos;
}


///////////////////////////
// EOF
///////////////////////////
