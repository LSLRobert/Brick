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
  
  // test the array class
  test_main();
  
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
    
    
    LS_RenderFrameGraphics();
    
    
    // temp solution
//    Sleep(1);
  }
  
Exit:
  
  return 0;
}


///////////////////////////
// EOF
///////////////////////////
