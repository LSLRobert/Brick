////////////////////////////////////////////////////////////
//
// Last Straw Labs, Inc.
// www.laststrawlabs.com
// July 27, 2022
//
////////////////////////////////////////////////////////////


#define Kilobyte(Value) (Value * 1024LL)
#define Megabyte(Value) (Value * 1024LL * 1024)
#define Gigabyte(Value) (Value * 1024LL * 1024 * 1024)

// fields/struct
LS_Memory my_memory;

// test_init_memory
void test_init_memory()
{
  //
  puts("\nSTART -- Testing MEMORY\n");
  
  my_memory = LS_MemoryNew(Megabyte(4));
  printf("Memory Address: %p\n", my_memory->address);
  printf("Memory Size:    %d\n", my_memory->size);
  
  puts("\nEND   -- Testing MEMORY\n");
}


// test_loop_memory
void test_loop_memory()
{
  //
}


// test_exit_memory
void test_exit_memory()
{
  //
  puts("\nSTART -- Testing MEMORY\n");
  
  LS_MemoryFree(my_memory);
  puts("Memory Free\n");
  
  puts("\nEND   -- Testing MEMORY\n");
}


///////////////////////////
// EOF
///////////////////////////
