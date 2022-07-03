#include <stdio.h>

// include "harold.h"
void __declspec( dllimport ) run();

// main
int main(int argc, char** argv)
{
  printf("Sandbox::main\n");
  
  run();
  
  return 0;
}
