////////////////////////////////////////////////////////////
//
// Last Straw Labs, Inc.
// www.laststrawlabs.com
// July 1, 2022
//
////////////////////////////////////////////////////////////
#include <harold.h>
#include "main.h"


///////////////////////////
// Testing
///////////////////////////

// testing includes
#include "test_memory.c"
#include "test_array.c"

// test_init
void test_init()
{
  //
  test_init_memory();
  test_init_array();
}

// test_loop
void test_loop()
{
  //
  test_loop_memory();
  test_loop_array();
}

// test_exit
void test_exit()
{
  //
  test_exit_memory();
  test_exit_array();
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
