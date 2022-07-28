////////////////////////////////////////////////////////////
//
// Last Straw Labs, Inc.
// www.laststrawlabs.com
// July 17, 2022
//
////////////////////////////////////////////////////////////
#include "header.h"
#include "array_int.h"

/* ls_list_new */
LS_HAROLD_API ls_list ls_list_new(ls_memory arena, usize size)
{
//  LS_List list = malloc(sizeof(struct LS_List_));
  ls_list list = ls_malloc(arena, sizeof(struct ls_list_));
  list->isize = size;
  list->count = 0;
  list->max = 0;
  list->arena = arena;
  list->items = NULL;
}


/* ls_list_free */
LS_HAROLD_API void  ls_list_free(ls_list list)
{
  ls_free(list->arena, list->items);
  ls_free(list->arena, list);
}


/* ls_list_add */
LS_HAROLD_API void* ls_list_add(ls_list list, void* item)
{
  u8* pos = NULL;
  
  if (list->items == NULL)
  {
//    list->items = malloc(list->isize);
    list->items = ls_malloc(list->arena, list->isize);
    list->max = 1;
  }
  else if (list->count == list->max)
  {
    size_t size = list->isize * list->max * 2;
//    void* items = realloc(list->items, size);
    void* items = ls_realloc(list->arena, list->items, size);
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


/* ls_list_rm */
LS_HAROLD_API void  ls_list_rm(ls_list list, void* item)
{
  u8* pos = (u8*)list->items;
  size_t tail_size = 0;
  
  for (int i=0; i < list->count; ++i)
  {
    if (memcmp(pos, item, list->isize) == 0) /* 0 SUCCESS/NO_ERROR */
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
    void* items = ls_realloc(list->arena, list->items, size);
    if (items == NULL)
    {
      puts("realloc failed!");
      exit(EXIT_FAILURE);
    }
    list->items = items;
    list->max /= 2;
  }
}


/* ls_list_remove */
LS_HAROLD_API void  ls_list_remove(ls_list list, void* item)
{
  ls_list_rm(list, item);
}


/* ls_list_get */
LS_HAROLD_API void* ls_list_get(ls_list list, i32 num)
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


/* ls_list_set */
LS_HAROLD_API void* ls_list_set(ls_list list, i32 num, void* item)
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
