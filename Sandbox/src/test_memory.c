////////////////////////////////////////////////////////////
//
// Last Straw Labs, Inc.
// www.laststrawlabs.com
// July 27, 2022
//
////////////////////////////////////////////////////////////


/* fields and struct */
ls_memory my_memory;

/* test_init_memory */
void test_init_memory()
{
  /* Testing MEMORY */
  puts("\nSTART -- Testing MEMORY\n");
  
  my_memory = ls_memory_new(Megabyte(4));
  printf("Memory Address: %p\n", my_memory->address);
  printf("Memory Size:    %d\n", my_memory->size);
  
  puts("\nEND   -- Testing MEMORY\n");
}


/* test_loop_memory */
void test_loop_memory()
{
  
}


/* test_exit_memory */
void test_exit_memory()
{
  /* Testing MEMORY */
  puts("\nSTART -- Testing MEMORY\n");
  
  ls_memory_free(my_memory);
  puts("Memory Free\n");
  
  puts("\nEND   -- Testing MEMORY\n");
}


///////////////////////////
// EOF
///////////////////////////
