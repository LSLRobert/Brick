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
  
  // game loop
//  while (should_quit) 
//  {
//    SDL_Event event;
//    
//    while (SDL_PollEvent(&event))
//    {
//      switch (event.type) 
//      {
//        case SDL_QUIT: 
//          should_quit = true;
//          break;
//        default:
//          break;
//      }
//      
//    }
//    
//  }
  
Exit:
  
  return 0;
}
