////////////////////////////////////////////////////////////
//
// Last Straw Labs, Inc.
// www.laststrawlabs.com
// July 1, 2022
//
////////////////////////////////////////////////////////////
#include <harold.h>
#include "main.h"


// Testing
#include "memory.c"

///////////////////////////
// TEST:: struct
///////////////////////////
typedef struct vec3
{
  float x;
  float y;
  float z;
} vec3;

// print
void print(LS_List list)
{
  for (int i=0; i < list->count; i++)
  {
    vec3* me_print = LS_ListGet(list, i);
    printf("%d -> ( %.1f, %.1f, %.1f )\n", i, me_print->x, me_print->y, me_print->z);
  }
  printf("max:   %d\n", list->max);
  printf("count: %d\n", list->count);
  puts("...\n");
}


#define Kilobyte (1024)
#define Megabyte (1024 * 1024)
#define Gigabyte (1024 * 1024 * 1024)

// test_init
void test_init()
{
  test_main();
  
  /////////////////////////////////////
  
  void* my_memory = NULL;
//  puts("\nSTART -- Testing get MEMORY\n");
//  
//  LS_Memory my_memory = LS_MemoryNew(4 * Megabyte);
//  printf("Memory: %p\n", my_memory);
//  
//  puts("END -- Testing get MEMORY\n");
  
  /////////////////////////////////////
  
  puts("\nSTART -- Testing Array\n");
  
  LS_List my_list = LS_ListNew(my_memory, sizeof(vec3));
  vec3 a = {  0.5,  0.5,  0.5 };
  vec3 b = {  0.5, -0.5,  0.5 };
  vec3 c = { -0.5, -0.5,  0.5 };
  vec3 d = { -0.5,  0.5,  0.5 };
  vec3 e = {  0.5,  0.5, -0.5 };
  vec3 f = {  0.5, -0.5, -0.5 };
  vec3 g = { -0.5, -0.5, -0.5 };
  vec3 h = { -0.5,  0.5, -0.5 };
  
  
  LS_ListAdd(my_list, &a);
  LS_ListAdd(my_list, &b);
  LS_ListAdd(my_list, &c);
  LS_ListAdd(my_list, &d);
  LS_ListAdd(my_list, &e);
  vec3* test5 = LS_ListAdd(my_list, &f);
  LS_ListAdd(my_list, &g);
  LS_ListAdd(my_list, &h );
  
  print(my_list);
  
  // pointer from list_add
  printf("pointer: ( %.1f, %.1f, %.1f )\n", test5->x, test5->y, test5->z);
  
  // pointer list_get
  vec3* get_print = LS_ListGet(my_list, 5);
  printf("get: ( %.1f, %.1f, %.1f )\n", get_print->x, get_print->y, get_print->z);
  
  // list_set test
  vec3 tens = { -10.0, -10.0, -10.0 };
  LS_ListSet(my_list, 4, &tens);
  
  print(my_list);
  
  LS_ListFree(my_memory, my_list);
  
  puts("END -- Testing Array\n");
  
  /////////////////////////////////////
  
//  puts("\nSTART -- Testing free MEMORY\n");
//  
//  LS_MemoryFree(my_memory);
//  
//  puts("END -- Testing free MEMORY\n");
  
  /////////////////////////////////////
  
}

// test_loop
void test_loop()
{
  
}

// test_exit
void test_exit()
{
  
}

///////////////////////////
// main
///////////////////////////
int main(int argc, char** argv)
{
  printf("Welcome to the Sandbox\n");
  
  // window
  LS_WindowSetVersionGL(3, 3);
  LS_WindowSetViewport(400, 300);
  LS_Window window = LS_WindowCreateGL("App Name", 800, 600, false);
  if (!window) 
  {
    // TODO: LOG ERROR
    printf("Window Init Failed\n");
    goto Exit;
  }
  
  // Log
  LS_LogCurrentWindowVersion();
  
  // Event Queue
  LS_Event event;
  
  // test init before loop
  test_init();
  
  // game loop
  while (LS_IsApplicationRunning())
  {
    while (LS_PollEvent(&event))
    {
      switch (event.type)
      {
//        case MSG_CLOSE:
//        case MSG_QUIT:
//        {
//          LS_SetApplicationRunning(false);
//          break;
//        }
        
        default:
        {
          break;
        }
        
      }
    } // PollEvent
    
    // testing in loop
    test_loop();

    LS_RenderFrameGraphics();
    
    
    // temp solution
//    Sleep(1);
  }
  
Exit:
  
  // testing at exit
  test_exit();
  
  return 0;
}


///////////////////////////
// EOF
///////////////////////////
