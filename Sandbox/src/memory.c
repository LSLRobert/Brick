// test_main

typedef struct Complex
{
  double r; // Real Part
  double c; // Complex Part
} Complex;

// test_main
void test_main()
{
    puts("\nSTART -- TESTING MEMORY\n");
  
  Complex array[1000];
  
  for (int i = 0;i < 5000; i++)
  {
    for (int j = 0;j < 1000; j++)
    {
      array[j] = new Complex(i, j)
    }
    for (int j = 0;j < 1000; j++)
    {
      delete array[j];
    }
  }
  
  
  
  puts("END -- TESTING MEMORY\n");
  
} // test_main

