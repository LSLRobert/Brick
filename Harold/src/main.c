#include <stdio.h>

// include "harold.h"
void __declspec( dllexport ) run();

// dead main
int main(int argc, char** argv)
{
  return 0;
}

// public function
void run()
{
  
  printf("This is the Harold RUN call :0\n");
  
}
