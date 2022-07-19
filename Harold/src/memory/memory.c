////////////////////////////////////////////////////////////
//
// Last Straw Labs, Inc.
// www.laststrawlabs.com
// July 17, 2022
//
////////////////////////////////////////////////////////////
#include "header.h"
#include "memory_int.h"


// LS_MemoryNew
LS_HAROLD_API LS_Memory LS_MemoryNew(uSize sizeBytes)
{
  // LPVOID VirtualAlloc(lpAddress, dwSize, flAllocationType, flProtect);
  void* Result = VirtualAlloc(NULL, sizeBytes, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
  if(Result == NULL)
  {
    puts("VirtualAlloc failed!");
    exit(EXIT_FAILURE);
  }
  return Result;
}

// LS_MemoryFree
LS_HAROLD_API void LS_MemoryFree(LS_Memory address)
{
  VirtualFree(address, 0, MEM_RELEASE);
}

// LS_Malloc
LS_HAROLD_API void* LS_Malloc(LS_Memory address, uSize size)
{
  // void* malloc(uSize size)
  return malloc(size);
  
}

// LS_Calloc
LS_HAROLD_API void* LS_Calloc(LS_Memory address, uSize numItems, uSize sizeItems)
{
  //
  return calloc(numItems, sizeItems);
  
}

// LS_Realloc
LS_HAROLD_API void* LS_Realloc(LS_Memory address, void* memory, uSize sizeNew)
{
  //
  return realloc(memory, sizeNew);
  
}

// LS_Free
LS_HAROLD_API void LS_Free(LS_Memory address, void* memory)
{
  //
  free(memory);
  
}

// LS_MemoryDisplay
LS_HAROLD_API void LS_MemoryDisplay(LS_Memory address)
{
  //
}

// LS_MemoryPrint
LS_HAROLD_API void LS_MemoryPrint(LS_Memory address)
{
  //
}


///////////////////////////
// EOF
///////////////////////////
