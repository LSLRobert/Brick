////////////////////////////////////////////////////////////
//
// Last Straw Labs, Inc.
// www.laststrawlabs.com
// July 27, 2022
//
////////////////////////////////////////////////////////////


// vec3 struct for testing
typedef struct vec3
{
  float x;
  float y;
  float z;
} vec3;

LS_List my_list;
LS_List empty_list;

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


// test_init_array
void test_init_array()
{
  //
  puts("\nSTART -- Testing Array\n");
  
  my_list = LS_ListNew(my_memory, sizeof(vec3));
  puts("Create Array\n");
  vec3 a = {  0.5,  0.5,  0.5 };
  vec3 b = {  0.5, -0.5,  0.5 };
  vec3 c = { -0.5, -0.5,  0.5 };
  vec3 d = { -0.5,  0.5,  0.5 };
  vec3 e = {  0.5,  0.5, -0.5 };
  vec3 f = {  0.5, -0.5, -0.5 };
  vec3 g = { -0.5, -0.5, -0.5 };
  vec3 h = { -0.5,  0.5, -0.5 };
  
  LS_ListAdd(my_list, &a);
  puts("Array add -a-\n");
  printf("Count: %d\n", my_list->count);
  LS_ListAdd(my_list, &b);
  puts("Array add -b-\n");
  printf("Count: %d\n", my_list->count);
  LS_ListAdd(my_list, &c);
  puts("Array add -c-\n");
  printf("Count: %d\n", my_list->count);
  LS_ListAdd(my_list, &d);
  puts("Array add -d-\n");
  printf("Count: %d\n", my_list->count);
  LS_ListAdd(my_list, &e);
  puts("Array add -e-\n");
  printf("Count: %d\n", my_list->count);
  vec3* test5 = LS_ListAdd(my_list, &f);
  puts("Array add -f-\n");
  printf("Count: %d\n", my_list->count);
  LS_ListAdd(my_list, &g);
  puts("Array add -g-\n");
  printf("Count: %d\n", my_list->count);
  LS_ListAdd(my_list, &h );
  puts("Array add -h-\n");
  printf("Count: %d\n", my_list->count);
  
//  print(my_list);
//  
//  // pointer from list_add
//  printf("pointer: ( %.1f, %.1f, %.1f )\n", test5->x, test5->y, test5->z);
//  
//  // pointer list_get
//  vec3* get_print = LS_ListGet(my_list, 5);
//  printf("get: ( %.1f, %.1f, %.1f )\n", get_print->x, get_print->y, get_print->z);
//  
//  // list_set test
//  vec3 tens = { -10.0, -10.0, -10.0 };
//  LS_ListSet(my_list, 4, &tens);
//  
//  print(my_list);
  
  
  puts("Create Empty List\n");
  empty_list = LS_ListNew(my_memory, sizeof(vec3));
  
  puts("END -- Testing Array\n");
}


// test_loop_array
void test_loop_array()
{
  //
}


// test_exit_array
void test_exit_array()
{
  //
  puts("\nSTART -- Testing ARRAY\n");
  
  printf("Count: %d\n", my_list->count);
  LS_ListFree(my_list);
  
  puts("FREE Empty List\n");
  LS_ListFree(empty_list);
  
  puts("Array Free\n");
  
  puts("\nEND   -- Testing ARRAY\n");
}



#if 0

  
  
  

#endif 


///////////////////////////
// EOF
///////////////////////////
