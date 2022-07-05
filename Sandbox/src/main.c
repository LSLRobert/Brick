// c includes
#include <stdio.h>

// engine includes
#include <harold.h>

// main
int main(int argc, char** argv)
{
  printf("Welcome to the Sandbox\n");
  
  // window
  WindowSetVersionGL(3, 3);
  WindowSetViewport(400, 300);
  Window window = WindowCreateGL("App Name", 800, 600, false);
  if (!window) 
  {
    // TODO: LOG ERROR
    printf("Window Init Failed\n");
    goto Exit;
  }
  
  // Log
  LogCurrentWindowVersion();
  
  // Event Queue
  Event event;
  
  // game loop
  while (IsApplicationRunning())
  {
    while (PollEvent(&event))
    {
      switch (event.type)
      {
//        case MSG_CLOSE:
//        case MSG_QUIT:
//        {
//          SetApplicationRunning(false);
//          break;
//        }
        
        default:
        {
          break;
        }
        
      }
    } // PollEvent
    
    
    RenderFrameGraphics();
    
    
    // temp solution
//    Sleep(1);
  }
  
Exit:
  
  return 0;
}
