#include <stdio.h>

#include <harold.h>

// main
int main(int argc, char** argv)
{
  printf("Sandbox::main\n");
  
  Window window = CreateWindow("App Name", 0, 0, 800, 600);
  
  if (!window)
  {
    printf("Window Init Failed %d\n", window);
    
    goto Exit;
  }
  
  CreateGLContext(window);
  
  
  
Exit:
  
  return 0;
}
