////////////////////////////////////////////////////////////
//
// Last Straw Labs, Inc.
// www.laststrawlabs.com
// July 9, 2022
//
// Array Backed List
// https://www.youtube.com/watch?v=-2CYCHLZXD4
//
////////////////////////////////////////////////////////////
#include <harold.h>
#include "array.h"


// list_new
struct list* list_new(size_t size)
{
  struct list* list = malloc(sizeof(struct list));
  list->isize = size;
  list->count = 0;
  list->max = 0;
  list->items = NULL;
}


// list_free
void list_free(struct list* list)
{
  if (list->count > 0)
  {
    free(list->items);
  }
  free(list);
}


// list_add
void* list_add(struct list *list, void* item)
{
  char* pos = NULL;
  
  if (list->items == NULL)
  {
    list->items = malloc(list->isize);
    list->max = 1;
  }
  else if (list->count == list->max)
  {
    size_t size = list->isize * list->max * 2;
    void* items = realloc(list->items, size);
    if (items == NULL)
    {
      puts("realloc failed!");
      exit(EXIT_FAILURE);
    }
    list->items = items;
    list->max *= 2;
  }
  
  pos = (char*)list->items + (list->count * list->isize);
  
  if (memcpy(pos, item, list->isize) == NULL)
  {
    puts("memccpy failed!");
    exit(EXIT_FAILURE);
  }
  
  list->count++;
  return pos;
}


// list_rm
void list_rm(struct list *list, void* item)
{
  char* pos = (char*)list->items;
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
  
  if (list->max > list->count*2)
  {
    size_t size = list->isize * (list->max / 2);
    void* items = realloc(list->items, size);
    if (items == NULL)
    {
      puts("realloc failed!");
      exit(EXIT_FAILURE);
    }
    list->items = items;
    list->max /= 2;
  }
  
}



///////////////////////////
// testing
///////////////////////////
// vec2
typedef struct vec3
{
  float x;
  float y;
  float z;
} vec3;

// print
void print(struct list *list)
{
  for (int i=0; i < list->count; i++)
  {
    vec3 me_print = *((vec3*)list->items+i);
    printf("%d -> ( %.1f, %.1f, %.1f )\n", i, me_print.x, me_print.y, me_print.z);
  }
  printf("max:   %d\n", list->max);
  printf("count: %d\n", list->count);
  puts("...\n");
}

// test_main
void test_main()
{
  puts("\nTesting Array\n");
  
  struct list* list = list_new(sizeof(vec3));
  vec3 a = {  0.5,  0.5,  0.5 };
  vec3 b = {  0.5, -0.5,  0.5 };
  vec3 c = { -0.5, -0.5,  0.5 };
  vec3 d = { -0.5,  0.5,  0.5 };
  vec3 e = {  0.5,  0.5, -0.5 };
  vec3 f = {  0.5, -0.5, -0.5 };
  vec3 g = { -0.5, -0.5, -0.5 };
  vec3 h = { -0.5,  0.5, -0.5 };
  
  list_add(list, &a);
  list_add(list, &b);
  list_add(list, &c);
  list_add(list, &d);
  list_add(list, &e);
  list_add(list, &f);
  list_add(list, &g);
  list_add(list, &h );
  
  print(list);
  
//  list_rm(list, &c);
//  print(list);
//  list_rm(list, &d);
//  print(list);
//  list_add(list, &a);
//  list_add(list, &b);
//  print(list);
  
  puts("END -- Testing Array\n");
}

///////////////////////////
// EOF
///////////////////////////
